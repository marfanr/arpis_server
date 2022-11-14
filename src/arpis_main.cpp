#include "rclcpp/rclcpp.hpp"
#include "arpis_server/network/udp.hpp"

class ServerNode : public rclcpp::Node {
  public:
  ServerNode() : Node("server_node") {
  arpis_server::udp(8080);
  }
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ServerNode>());
  return 0;
}
