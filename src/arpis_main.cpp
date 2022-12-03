#include <string>
#include "rclcpp/rclcpp.hpp"
#include "arpis_server/node/server_node.hpp"
#include "arpis_server/utils/arg_parser.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  if (argc == 1) {
    RCLCPP_ERROR(rclcpp::get_logger("main"), "argument not passed");
    return 0;
  }  

  rclcpp::Node::SharedPtr node  = std::make_shared<rclcpp::Node>("arpis_server");
  arpis_server::ServerNode * server = new arpis_server::ServerNode(
    node, 
    arpis_server::utils::ArgParser::get_addr(argc, argv),
    arpis_server::utils::ArgParser::get_port(argc, argv)
  );
  server->set_read_mode(arpis_server::utils::ArgParser::parse_mode(argv[1]));
  server->setup();
 
  rclcpp::executors::SingleThreadedExecutor exec;
  exec.add_node(node);
  rclcpp::Rate rcl_rate(8ms);
  while(rclcpp::ok()) {
    rcl_rate.sleep();
    exec.spin_some();  
  }
  
  rclcpp::shutdown();

  return 0;
}