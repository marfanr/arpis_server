#ifndef JOINT_HPP_
#define JOINT_HPP_

#include "arpis_network/tcp/tcp.hpp"

namespace arpis_server {

class Joint {
public:
    virtual void load_data();\
    virtual void publish(::arpis_network::tcp * tcp);
    Joint();
    virtual ~Joint();
protected:
private:
};

}

#endif