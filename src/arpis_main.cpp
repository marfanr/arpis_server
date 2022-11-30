#include <chrono>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include "rclcpp/rclcpp.hpp"
#include "arpis_network/tcp/tcp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tachimawari/control/control.hpp"
#include "tachimawari/joint/joint.hpp"
#include "tachimawari/joint/model/joint_id.hpp"
#include "tachimawari/joint/protocol_1/mx28_address.hpp"

#include "arpis_server/node/server_node.hpp"

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
  else if (argv[1] == (std::string)"cm740")
    id = 3;
  else
    RCLCPP_ERROR(rclcpp::get_logger("arpis_server"), "failied id, please specify use sdk, dummy, or cm740");

  const char * addr = "127.0.0.1";
  int port = 3000;
  for (int t = 0; t < argc; t++) {
    if (argv[t] == (std::string)"--addr")
      addr = (const char *)argv[t+1];
    else if (argv[t] == (std::string)"--port")
      port = (int)atoi(argv[t+1]);
  }

  // auto tcp = arpis_network::tcp(addr, port);
  // tcp.set_max_con(3);
  
  // auto node = std::make_shared<ServerNode>(id, addr, port);    
  rclcpp::Node::SharedPtr node  = std::make_shared<rclcpp::Node>("arpis_server");
  arpis_server::server_node * server = new arpis_server::server_node(node, addr, port);
  server->set_read_mode(id);
  server->setup();

  rclcpp::executors::MultiThreadedExecutor exec;
  exec.add_node(node);
  rclcpp::Rate rcl_rate(8ms);
  while(rclcpp::ok()) {
    rcl_rate.sleep();
    exec.spin_some();  
  }
  
  rclcpp::shutdown();

  // return 0;
}