#include <chrono>
#include <string>
#include <sys/socket.h>
#include "tachimawari/control/control.hpp"
#include "rclcpp/rclcpp.hpp"
#include "arpis_network/socket/socket.hpp"

using namespace std::chrono_literals;
class ServerNode : public rclcpp::Node {
public:
  ServerNode() : Node("server_node") {
    // timer_ = this->create_wall_timer(300ms, std::bind(&ServerNode::exec, this));
    this->exec();
  }
protected:
private:
  void exec() {
    auto socket = arpis_network::socket(AF_INET, SOCK_STREAM, 0);
  }
  rclcpp::TimerBase::SharedPtr timer_;    
};


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  if (argc == 1) {
    RCLCPP_ERROR(rclcpp::get_logger("main"), "argument not passed");
    return 0;
  }

 if (argv[1] == (std::string)"tcp") {
  rclcpp::spin(std::make_shared<ServerNode>());
 }

  return 0;
}

