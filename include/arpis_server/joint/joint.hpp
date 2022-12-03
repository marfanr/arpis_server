#ifndef JOINT_HPP_
#define JOINT_HPP_

#include "arpis_network/tcp/tcp.hpp"
#include "arpis_server/model/arpis.hpp"

namespace arpis_server {

class Joint {
public:
    virtual void load_data();
    virtual void increment();
    virtual int get_iteration();
    virtual arpis publish();
    virtual void set_position(int pos);
    Joint();
    virtual ~Joint();
protected:
private:
};

}

#endif