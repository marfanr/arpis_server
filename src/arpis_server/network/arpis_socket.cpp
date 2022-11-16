#include <sys/socket.h>
#include <cstring>
#include "arpis_server/network/arpis_socket.hpp"
#include <iostream>

arpis_server::arpis_socket::arpis_socket(int domain, int type, int protocol) {
    this->socket_ = socket(domain, type, protocol);    
    std::cout << this->get_socket() << std::endl;
}

void arpis_server::arpis_socket::assign_sockaddr(sockaddr_in * sockaddr) {       
    memset(sockaddr, '\0', sizeof(*sockaddr));
    this->sockaddr_vector_.push_back(sockaddr);    
}

int arpis_server::arpis_socket::sock_bind(int sockid) {
    return bind(this->get_socket(), (sockaddr*)&(*this->sockaddr_vector_.at(sockid)), sizeof(&this->sockaddr_vector_.at(sockid)));
}

int arpis_server::arpis_socket::get_socket() {
    return this-> socket_;
}

arpis_server::arpis_socket_response arpis_server::arpis_socket::receive(int buf_size, int flags, int sockid) {
    arpis_server::arpis_socket_response res;
    char buffer[buf_size];
    socklen_t t = sizeof(this->sockaddr_vector_.at(sockid));
    res.status = ::recvfrom(this->get_socket(), (char *)buffer, buf_size, flags, (sockaddr *)this->sockaddr_vector_.at(sockid), &t);
    std::cout << buffer << std::endl;
    res.buffer = buffer;
    return res;
}