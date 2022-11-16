#ifndef UDP_HPP_
#define UDP_HPP_
#include <stdlib.h>
#include <netinet/in.h>
#include "arpis_server/network/arpis_socket.hpp"

namespace arpis_server {

class udp : public arpis_socket {
public:
    udp(u_int16_t port);
protected:
    sockaddr_in si_me, si_other;
private:
};
}

#endif
