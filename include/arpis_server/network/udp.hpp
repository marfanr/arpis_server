#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstring>
#include <arpa/inet.h>

#pragma once

namespace arpis_server {

class udp {
    public:
    udp(u_int16_t port);
    protected:
    sockaddr_in si_me, si_other;
};
}
