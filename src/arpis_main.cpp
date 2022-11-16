#include <chrono>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "arpis_server/network/udp.hpp"
#include "tachimawari/control/control.hpp"

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
    arpis_server::udp(8080);
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

 if (argv[1] == (std::string)"udp") {
  rclcpp::spin(std::make_shared<ServerNode>());
 }

  return 0;
}

