#ifndef TCP_HPP_
#define TCP_HPP_

#include <stdlib.h>
#include <netinet/in.h>
#include "arpis_server/network/socket.hpp"

namespace arpis_server {

class tcp : public socket {
public:
    tcp(u_int16_t port);
protected:
    sockaddr_in si_me, si_other;
private:
};
}

#endif
