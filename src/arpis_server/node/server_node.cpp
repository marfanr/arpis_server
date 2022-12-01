#include <chrono>
#include "arpis_server/node/server_node.hpp"
#include "arpis_server/joint/joint.hpp"
#include "arpis_server/joint/tachimawari.hpp"
#include "arpis_server/joint/dummy.hpp"

namespace arpis_server {

ServerNode::ServerNode(rclcpp::Node::SharedPtr node, const char *addr, int port) : node_(node) {    
  tcp_ = new arpis_network::tcp(addr, port);
  tcp_->set_max_con(3);
  tcp_->serve();    
}

void ServerNode::setup() {
    using namespace std::chrono_literals;

    // setup read joint data
    switch (this->id)
    {
    case 1: /* SDK */
        joint_ = std::make_shared<Tachimawari>(1);
        joint_->load_data();
        timer_ = node_->create_wall_timer(8ms, std::bind(&ServerNode::read_joint_from_tachimawari, this));
        break;    

    case 2: /* Dummy */
      joint_ = std::make_shared<Dummy>();
      joint_->load_data(); 
      timer_ = node_->create_wall_timer(8ms, std::bind(&ServerNode::read_joint_from_dummy, this));        
      break;
    
    case 3: /* CM740 */
        joint_ = std::make_shared<Tachimawari>(2);
        joint_->load_data();       
        timer_ = node_->create_wall_timer(8ms, std::bind(&ServerNode::read_joint_from_tachimawari, this));
        break;

    default:
        break;
    }

}

void ServerNode::set_read_mode(int mode) {
   this->id = mode;
}

void ServerNode::read_joint_from_tachimawari() {
    auto item = this->joint_->publish();
    tcp_->send((char *)(void *)&item, sizeof(item));  
}

void ServerNode::read_joint_from_dummy() {
  auto item = this->joint_->publish();
  this->joint_->increment();
  tcp_->send((char *)(void *)&item, sizeof(item));            
  if (this->joint_->get_iteration() == 2) // limit to 2 looping 
    this->joint_->set_position(0);
}

}