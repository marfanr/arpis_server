#include <chrono>
#include "arpis_server/node/server_node.hpp"
#include "arpis_server/joint/joint.hpp"
#include "arpis_server/joint/tachimawari.hpp"

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
        // control_manager_ = std::make_shared<::tachimawari::control::DynamixelSDK>("/dev/ttyUSB0");
        // joint_manager_ = std::make_shared<::tachimawari::joint::JointManager>(control_manager_);
        // if (!control_manager_->connect()) {
        //     control_manager_->set_port("/dev/ttyUSB1");
        //     if (!control_manager_->connect()) {
        //         RCLCPP_ERROR(rclcpp::get_logger("arpis_server/ServerNode"), "can`t connect to sdk");   
        //         exit(0);     
        //     }
        // }
        timer_ = node_->create_wall_timer(8ms, std::bind(&ServerNode::read_joint_from_tachimawari, this));
        break;    


    case 2: /* Dummy */  
        this->set_dummy();
        timer_ = node_->create_wall_timer(8ms, std::bind(&ServerNode::read_joint_from_dummy, this));        
      break;
    
    case 3: /* CM740 */
        joint_ = std::make_shared<Tachimawari>(2);
        control_manager_ = std::make_shared<::tachimawari::control::CM740>("/dev/ttyUSB0"); // sdk only    
        joint_manager_ = std::make_shared<::tachimawari::joint::JointManager>(control_manager_);
        if (!control_manager_->connect()) {
            control_manager_->set_port("/dev/ttyUSB1");
            if (!control_manager_->connect()) {
                RCLCPP_ERROR(rclcpp::get_logger("arpis_server"), "failed connect cm740");
                exit(0);     
            }
        }         
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
    this->joint_->publish(this->tcp_);
    auto joints = joint_manager_->get_current_joints();
    std::vector<tachimawari::joint::Joint> new_joints(joints);
    for (auto & joint : new_joints) {
      float value = tachimawari::joint::Joint::CENTER_VALUE;

      int current_value = control_manager_->read_packet(
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
    tcp_->send((char *)(void *)&item, sizeof(item));  
}

void ServerNode::set_dummy() {
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
    dummy_item_[1][0] = {id: 6, position: 2000};
    dummy_item_[1][1] = {id: 6, position: 2090};   
    dummy_item_[1][2] = {id: 6, position: 2090};   
    dummy_item_[1][3] = {id: 6, position: 2100};   
    dummy_item_[1][4] = {id: 6, position: 2700};   
    dummy_item_[1][5] = {id: 6, position: 2100};   
    dummy_item_[1][6] = {id: 6, position: 2100};   
    dummy_item_[1][7] = {id: 6, position: 2500};   
    dummy_item_[1][8] = {id: 6, position: 2300};   
    dummy_item_[1][9] = {id: 6, position: 2500};   
    dummy_item_[1][10] = {id: 19, position: 2700};   
    dummy_item_[1][11] = {id: 19, position: 2700};
    dummy_item_[1][12] = {id: 18, position: 2100};   
    dummy_item_[1][13] = {id: 18, position: 2100};   
    dummy_item_[1][14] = {id: 18, position: 2500};   
    dummy_item_[1][15] = {id: 19, position: 2300};   
    dummy_item_[1][16] = {id: 19, position: 2500};   
    dummy_item_[1][17] = {id: 20, position: 2700};   
    dummy_item_[1][18] = {id: 20, position: 2700};  
}

void ServerNode::read_joint_from_dummy() {  
  arpis item;
    auto dummy = dummy_item_[dummy_readed];
    for (int i = 0; i < 20; i++) {
      item.i[i].id= dummy[i].id;
      item.i[i].position = dummy[i].position;
      // pos += 1;
    }
    // i.id = dummy.id;
    // i.position = dummy.position;
    tcp_->send((char *)(void *)&item, sizeof(item));            
    dummy_readed += 1;
    if (dummy_readed == 2) // limit to 5 looping 
      dummy_readed = 0;
}

}