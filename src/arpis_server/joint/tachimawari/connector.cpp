#include "arpis_server/joint/tachimawari.hpp"
#include "rclcpp/rclcpp.hpp"

namespace arpis_server {

Tachimawari::Tachimawari(int mode) {
    if (mode < 0 || mode > 2) {
        RCLCPP_ERROR(rclcpp::get_logger("arpis_esrver/joint/Tachimawari"), "invalid mode");
        exit(0);
    }
    this->mode = mode;
}

void Tachimawari::load_data() {
    if (this->mode == 0)
        control_manager_ = std::make_shared<::tachimawari::control::DynamixelSDK>("/dev/ttyUSB0");
    else
        control_manager_ = std::make_shared<::tachimawari::control::CM740>("/dev/ttyUSB0");
    joint_manager_ = std::make_shared<::tachimawari::joint::JointManager>(control_manager_);
    if (!control_manager_->connect()) {
        control_manager_->set_port("/dev/ttyUSB1");
        if (!control_manager_->connect())
            RCLCPP_ERROR(rclcpp::get_logger("arpis_server/ServerNode"), "can`t connect to sdk");        
    }
}

Tachimawari::~Tachimawari() {}

}