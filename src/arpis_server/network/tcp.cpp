#include "arpis_server/network/tcp.hpp"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstring>
#include <arpa/inet.h>
#include <string>

namespace arpis_server  {
tcp::tcp(uint16_t port) : socket(AF_INET, SOCK_STREAM, 0) {    
    int sock = ::socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "starting udp server" << std::endl;
    sockaddr_in sockaddr_me, sockadr_other;
    bzero(&sockaddr_me, sizeof(sockaddr_me));
    bzero(&sockadr_other, sizeof(sockadr_other));
    sockaddr_me.sin_family = AF_INET;
    sockaddr_me.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockaddr_me.sin_port = htons(3030);
    // int opt = 1;
    // if (setsockopt(this->get_socket(), SOL_SOCKET,
    //                SO_REUSEADDR | SO_REUSEPORT, &opt,
    //                sizeof(opt))) {
    //     std::cout << "error" << std::endl;
    // }
    // this->register_sockaddr(&sockaddr_me);
    // this->register_sockaddr(&sockaddr_other);    
    if (bind(sock, (sockaddr*)&sockaddr_me, sizeof(sockaddr_me)) < 0) {
        std::cout << "failied to bind socket" << std::endl;
    }
    else
        std::cout << "bind socket sucessfuly.." << std::endl;
    
    if (listen(sock, 3) < 0) {
        std::cout << "can`t listen connection" << std::endl;        
    }
    else 
        std::cout << "server listening.." << std::endl;
    socklen_t size = sizeof(sockadr_other);   

    if (accept(sock, (sockaddr*)&sockadr_other, &size) < 0) {
        std::cout <<  "Problem with client conection" << std::endl;
    } else
        std::cout << "Accept client call" << std::endl;

    std::cout << "test" << std::endl;




    // std::cout 
    // auto l = this->receive(1024, MSG_WAITALL, 1);
    // char buffer[1024];
    // socklen_t t = sizeof(sockaddr_other);

    // recvfrom(this->get_socket(), (char *)buffer, 1024, MSG_WAITALL, (sockaddr*)&sockaddr_other, &t);
    // std::cout << (std::string)buffer << std::endl;
    
    // int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // memset(&si_me, '\0', sizeof(si_me));
    // memset(&si_other, '\0', sizeof(si_other));
    // si_me.sin_fa{mily = AF_INET;
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
    // // sendto(sockfd, (char*)hello, strlen(hello), MSG_CONFIRM, (sockaddr*)&si_other, len);

    // std::cout << "sended from server" << std::endl;
};
}