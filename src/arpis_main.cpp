#include <chrono>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include "rclcpp/rclcpp.hpp"
#include "arpis_network/tcp/tcp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tachimawari/control/control.hpp"
#include "tachimawari/joint/joint.hpp"
#include "tachimawari/joint/model/joint_id.hpp"
#include "tachimawari/joint/protocol_1/mx28_address.hpp"

using namespace std::chrono_literals;

struct arpis_transfer_item {
  int id;
  int position;
};

struct arpis {
  arpis_transfer_item i[22];
};

class ServerNode : public rclcpp::Node {
public:
  ServerNode(int i, const char * addr, int port) : Node("server_node") {    
    // this->tcp = new arpis_network::tcp("192.168.100.3", 3333);    
    this->tcp = new arpis_network::tcp(addr, port);    
    tcp->set_max_con(3);
    tcp->serve();        
    if (i == 1) {
      control_ = std::make_shared<tachimawari::control::DynamixelSDK>("/dev/ttyUSB0"); // sdk only    
      joint_manager_ = std::make_shared<tachimawari::joint::JointManager>(control_);
      if (!control_->connect()) {
        control_->set_port("/dev/ttyUSB1");
        if (!control_->connect()) {
          RCLCPP_ERROR(rclcpp::get_logger("arpis_server"), "failed connect sdk");
        }
      }    
      timer_ = this->create_wall_timer(8ms, std::bind(&ServerNode::read_join, this));        
    }  else if (i == 2) { // dummy
      this->generate_dummy();
      timer_ = this->create_wall_timer(8ms, std::bind(&ServerNode::read_dummy, this));        
     } else if (i == 3) {
        control_ = std::make_shared<tachimawari::control::CM740>("/dev/ttyUSB0"); // sdk only    
        joint_manager_ = std::make_shared<tachimawari::joint::JointManager>(control_);
      if (!control_->connect()) {
        control_->set_port("/dev/ttyUSB1");
        if (!control_->connect()) {
          RCLCPP_ERROR(rclcpp::get_logger("arpis_server"), "failed connect cm740");
        }
      }
      timer_ = this->create_wall_timer(8ms, std::bind(&ServerNode::read_join, this));        
     }
  }
  
  void close() {
    this->tcp->close();
  }

protected:
private:
  void read_join() {
    auto joints = joint_manager_->get_current_joints();
    // joint_manager_->update_current_joints_from_control_manager(joints);    
    std::vector<tachimawari::joint::Joint> new_joints(joints);
    for (auto & joint : new_joints) {
      float value = tachimawari::joint::Joint::CENTER_VALUE;

      int current_value = control_->read_packet(
        joint.get_id(), tachimawari::joint::protocol_1::MX28Address::PRESENT_POSITION_L, 2);

      value = (current_value == -1) ? value : current_value;

      joint.set_position_value(value);

    }
      for (const auto & joint : new_joints){
        for (auto & current_joint : joints) {
          if (current_joint.get_id() == joint.get_id()) {
            current_joint.set_position(joint.get_position());
            current_joint.set_pid_gain(
              joint.get_pid_gain()[0], joint.get_pid_gain()[1], joint.get_pid_gain()[2]);

            break;
          }
        }
      }
    arpis item;
    int pos = 0;
    for (auto joint: joints) {
      RCLCPP_INFO(rclcpp::get_logger("arpis_server"), "s %i : %i", joint.get_id(), joint.get_position_value());          
      item.i[pos].id = static_cast<int>(joint.get_id());
      item.i[pos].position = joint.get_position_value();  
      pos+=1;
    }    
    tcp->send((char *)(void *)&item, sizeof(item));            
  }  

  void read_dummy() {    
    // int pos = 0;
    arpis item;
    auto dummy = dummy_item_[dummy_readed];
    for (int i = 0; i < 20; i++) {
      item.i[i].id= dummy[i].id;
      item.i[i].position = dummy[i].position;
      // pos += 1;
    }
    // i.id = dummy.id;
    // i.position = dummy.position;
    tcp->send((char *)(void *)&item, sizeof(item));            
    dummy_readed += 1;
    if (dummy_readed == 1) 
      dummy_readed = 0;
  }  

  void generate_dummy() {
    for (int i = 0; i < 1000; i ++) {
      for (int x = 0; x < 20; x++) {
        dummy_item_[i][x].id = x;
        dummy_item_[i][x].position = 2048;
      }
    }
    dummy_item_[0][0] = {id: 1, position: 2069};
    dummy_item_[0][1] = {id: 2, position: 2780};
    dummy_item_[0][2] = {id: 1, position: 2100};
    dummy_item_[0][3] = {id: 2, position: 2670};
    dummy_item_[0][4] = {id: 1, position: 2300};
    dummy_item_[0][5] = {id: 2, position: 2000};
    dummy_item_[0][6] = {id: 1, position: 1080};
    dummy_item_[0][7] = {id: 2, position: 2090};   
    dummy_item_[0][8] = {id: 1, position: 2090};   
    dummy_item_[0][9] = {id: 2, position: 2090};   
    dummy_item_[0][10] = {id: 1, position: 2090};   
    dummy_item_[0][11] = {id: 2, position: 2090};   
    dummy_item_[0][12] = {id: 1, position: 2100};   
    dummy_item_[0][13] = {id: 2, position: 2700};   
    dummy_item_[0][14] = {id: 1, position: 2100};   
    dummy_item_[0][15] = {id: 2, position: 2100};   
    dummy_item_[0][16] = {id: 1, position: 2500};   
    dummy_item_[0][17] = {id: 2, position: 2300};   
    dummy_item_[0][18] = {id: 2, position: 2500};   
    dummy_item_[0][19] = {id: 2, position: 2700};   
    
    
  }

  arpis_network::tcp * tcp;
  rclcpp::TimerBase::SharedPtr timer_;  
  std::shared_ptr<tachimawari::control::ControlManager> control_;
  std::shared_ptr<tachimawari::joint::JointManager> joint_manager_;
  arpis_transfer_item dummy_item_[1000][20];
  int dummy_readed = 0;
};


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  if (argc == 1) {
    RCLCPP_ERROR(rclcpp::get_logger("main"), "argument not passed");
    return 0;
  }  

  int id;
  if (argv[1] == (std::string)"sdk")
    id = 1;
  else if (argv[1] == (std::string)"dummy") 
    id = 2;
  if (argv[1] == (std::string)"cm740")
    id = 3;

  const char * addr = "127.0.0.1";
  int port = 3000;
  for (int t = 0; t < argc; t++) {
    if (argv[t] == (std::string)"--addr")
      addr = (const char *)argv[t+1];
    else if (argv[t] == (std::string)"--port")
      port = (int)atoi(argv[t+1]);
  }

  
  // auto node = std::make_shared<ServerNode>(id, addr, port);
  auto node  = std::make_shared<rclcpp::Node>("arpis_server");

  // rclcpp::executors::MultiThreadedExecutor exec;
  // exec.add_node(node);
  // rclcpp::Rate rcl_rate(8ms);
  // while(rclcpp::ok()) {
  //   rcl_rate.sleep();
  //   exec.spin_some();  
  // }
  // // node->close();
  // rclcpp::shutdown();

  // return 0;
}
