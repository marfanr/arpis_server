#ifndef SERVER_NODE_
#define SERVER_NODE_

#include "rclcpp/rclcpp.hpp"
#include "arpis_network/tcp/tcp.hpp"
#include "tachimawari/control/control.hpp"
#include "tachimawari/joint/joint.hpp"
#include "tachimawari/joint/model/joint_id.hpp"
#include "tachimawari/joint/protocol_1/mx28_address.hpp"
#include "rclcpp/rclcpp.hpp"
#include "arpis_server/model/arpis.hpp"
#include "arpis_server/joint/joint.hpp"

namespace arpis_server {

class ServerNode {
public:
    ServerNode(rclcpp::Node::SharedPtr node, const char *addr, int port);
    void setup();
    void set_read_mode(int mode);
protected:
    std::shared_ptr<Joint> joint_;
    void read_joint_from_tachimawari();
    void read_joint_from_dummy();
    void set_dummy();
private:
    arpis_network::tcp *tcp_;
    std::shared_ptr<rclcpp::Node> node_;    
    int id = 0;
    rclcpp::TimerBase::SharedPtr timer_;
};

}

#endif