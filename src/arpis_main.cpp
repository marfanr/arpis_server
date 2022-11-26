#include <chrono>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include "rclcpp/rclcpp.hpp"
#include "arpis_network/tcp/tcp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tachimawari/control/control.hpp"
#include "tachimawari/joint/joint.hpp"

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
  ServerNode(int i) : Node("server_node") {    
    // this->tcp = new arpis_network::tcp("192.168.100.3", 3333);    
    this->tcp = new arpis_network::tcp("127.0.0.1", 3333);    
    tcp->set_max_con(3);
    tcp->serve();        
    control_ = std::make_shared<tachimawari::control::DynamixelSDK>("/dev/ttyUSB0"); // sdk only    
    joint_manager_ = std::make_shared<tachimawari::joint::JointManager>(control_);
    if (i == 1) {
      if (!control_->connect()) {
        control_->set_port("/dev/ttyUSB1");
        if (!control_->connect()) {
          RCLCPP_ERROR(rclcpp::get_logger("arpis_server"), "failed connect sdk");
        }
      }
      timer_ = this->create_wall_timer(1s, std::bind(&ServerNode::read_join, this));        
    }  else if (i == 2) {
      this->generate_dummy();
      timer_ = this->create_wall_timer(800ms, std::bind(&ServerNode::read_dummy, this));        
    }
  }
  
  void close() {
    this->tcp->close();
  }

protected:
private:
  void read_join() {
    auto joints = joint_manager_->get_current_joints();
    arpis item;
    int pos = 0;
    for (auto joint: joints) {
      RCLCPP_INFO(rclcpp::get_logger("arpis_server"), "s %i : %i", joint.get_id(), joint.get_position_value());          
      item.i[pos].id = static_cast<int>(joint.get_id());
      item.i[pos].position = joint.get_position_value();
    //   i.id = static_cast<int>(joint.get_id());
    //   i.position = joint.get_position_value();
    //   item[pos] = i;
      pos+=1;
    }
      tcp->send(reinterpret_cast<char *>(&item), sizeof(arpis));        
  }  

  void read_dummy() {    
    // int pos = 0;
    arpis item;
    auto dummy = dummy_item_[dummy_readed];
    for (int i = 0; i < 22; i++) {
      item.i[i].id= dummy[i].id;
      item.i[i].position = dummy[i].position;
      // pos += 1;
    }
    // i.id = dummy.id;
    // i.position = dummy.position;
    tcp->send((char *)(void *)&item, sizeof(item));            
    dummy_readed += 1;
  }  

  void generate_dummy() {
    dummy_item_[0][0] = {id: 20, position: 4096};
    dummy_item_[0][1] = {id: 19, position: 4096};
    dummy_item_[0][2] = {id: 19, position: 4096};
    dummy_item_[0][3] = {id: 15, position: 4096};
    
  }

  arpis_network::tcp * tcp;
  rclcpp::TimerBase::SharedPtr timer_;  
  std::shared_ptr<tachimawari::control::ControlManager> control_;
  std::shared_ptr<tachimawari::joint::JointManager> joint_manager_;
  arpis_transfer_item dummy_item_[100][100];
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
  
  auto node = std::make_shared<ServerNode>(id);
  rclcpp::spin(node);  
  // node->close();
  rclcpp::shutdown();

  return 0;
}
