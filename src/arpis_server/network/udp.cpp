#include "arpis_server/network/udp.hpp"
#include <iostream>

arpis_server::udp::udp(uint16_t port) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&si_me, '\0', sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = inet_addr("127.0.0.1");
    int status = bind(sockfd, (sockaddr*)&si_me, sizeof(si_me));        
    std::cout << status << std::endl;
}