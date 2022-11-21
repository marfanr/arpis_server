#include "arpis_server/network/udp.hpp"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstring>
#include <arpa/inet.h>
#include <string>

arpis_server::udp::udp(uint16_t port) : arpis_socket(AF_INET, SOCK_DGRAM, 0) {    
    std::cout << "starting udp server" << std::endl;
    sockaddr_in sockaddr_me, sockaddr_other;
    sockaddr_me.sin_family = AF_INET;
    sockaddr_me.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockaddr_me.sin_port = htons(port);
    this->assign_sockaddr(&sockaddr_me);
    this->assign_sockaddr(&sockaddr_other);    
    std::cout << this->sock_bind(0) << std::endl;
    auto l = this->receive(1024, MSG_WAITALL, 1);
    std::cout << (std::string)l.buffer << std::endl;
    
    // int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // memset(&si_me, '\0', sizeof(si_me));
    // memset(&si_other, '\0', sizeof(si_other));
    // si_me.sin_family = AF_INET;
    // si_me.sin_port = htons(port);
    // si_me.sin_addr.s_addr = inet_addr("127.0.0.1");
    // int status = bind(sockfd, (sockaddr*)&si_me, sizeof(si_me));            
    // // socklen_t addrzie = sizeof(si_me);
    // char buffer[1024];
    // // strcpy(buffer, "HELLO \n");
    // socklen_t len = sizeof(si_other);
    // char *hello = "hello from server";
    // std::cout << "waiting client..." << std::endl;
    // recvfrom(sockfd, (char*)buffer, 1024, MSG_WAITALL, (sockaddr*)&si_other, &len);
    // std::string msg = buffer;    
    // std::cout << msg << std::endl;
    // sendto(sockfd, (char*)hello, strlen(hello), MSG_CONFIRM, (sockaddr*)&si_other, len);

    // std::cout << "sended from server" << std::endl;
}