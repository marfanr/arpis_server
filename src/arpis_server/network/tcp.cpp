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

};

}