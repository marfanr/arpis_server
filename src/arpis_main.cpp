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
  float position;
};

class ServerNode : public rclcpp::Node {
public:
  ServerNode(int i) : Node("server_node") {    
    tcp = new arpis_network::tcp("127.0.0.1", 3030);    
    tcp->serve();        
    control_ = std::make_shared<tachimawari::control::DynamixelSDK>("/dev/ttyUSB0"); // sdk only    
    joint_manager_ = std::make_shared<tachimawari::joint::JointManager>(control_);
    if (i == 1)
      timer_ = this->create_wall_timer(8ms, std::bind(&ServerNode::read_join, this));        
    else if (i == 2) {
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
    for (auto joint: joints) {
      arpis_transfer_item i;
      i.id = static_cast<int>(joint.get_id());
      i.position = joint.get_position();
      tcp->send((char *)(void *)&i, sizeof(i));        
    }
  }  

  void read_dummy() {    
    auto dummy = dummy_item_[dummy_readed];
    arpis_transfer_item i;
    i.id = dummy.id;
    i.position = dummy.position;
    tcp->send((char *)(void *)&i, sizeof(i));            
    dummy_readed += 1;
  }  

  void generate_dummy() {
    dummy_item_[0] = {id: 20, position: 10.0};
    dummy_item_[1] = {id: 19, position: 20.0};
    dummy_item_[2] = {id: 15, position: 10.0};
    dummy_item_[3] = {id: 1, position: 20.0};
    dummy_item_[4] = {id: 4, position: 70.0};
    dummy_item_[5] = {id: 2, position: 0.0};
    dummy_item_[6] = {id: 5, position: 60.0};
    dummy_item_[7] = {id: 20, position: 60.0};
    dummy_item_[8] = {id: 16, position: 60.0};
    dummy_item_[9] = {id: 14, position: 20.0};
    dummy_item_[10] = {id: 12, position: 60.0};
    dummy_item_[11] = {id: 11, position: 10.0};
    dummy_item_[12] = {id: 1, position: 30.0};
    dummy_item_[13] = {id: 4, position: 10.0};
    dummy_item_[14] = {id: 3, position: 20.0};
    dummy_item_[15] = {id: 4, position: 30.0};
  }

  arpis_network::tcp * tcp;
  rclcpp::TimerBase::SharedPtr timer_;  
  std::shared_ptr<tachimawari::control::ControlManager> control_;
  std::shared_ptr<tachimawari::joint::JointManager> joint_manager_;
  arpis_transfer_item dummy_item_[100];
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
  node->close();
  rclcpp::shutdown();

  return 0;
}

