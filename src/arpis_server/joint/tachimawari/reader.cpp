#include "arpis_server/joint/tachimawari.hpp"

namespace arpis_server {

arpis Tachimawari::publish()
{
    // this->joint_->publish(this->tcp_);
    auto joints = this->joint_manager_->get_current_joints();
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
    return item;
}

}