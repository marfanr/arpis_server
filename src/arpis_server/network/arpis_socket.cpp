#include <sys/socket.h>
#include <cstring>
#include "arpis_server/network/arpis_socket.hpp"
#include <iostream>

arpis_server::arpis_socket::arpis_socket(int domain, int type, int protocol) {
    if (this->socket_ = socket(domain, type, protocol)) {
        std::cout << "error creating socket" << std::endl;
    }
}

int arpis_server::arpis_socket::get_socket() {
    return this->socket_;
}

void arpis_server::arpis_socket::register_sockaddr(sockaddr_in * sockaddr) {
    memset(sockaddr, '\0', sizeof(*sockaddr));
    this->sockaddr_.push_back(sockaddr);
}

sockaddr_in * arpis_server::arpis_socket::get_sockaddr(int id) {
    return this->sockaddr_.at(id);
}

int arpis_server::arpis_socket::sock_bind(int sockid) {
    return bind(this->get_socket(), (sockaddr*)this->get_sockaddr(sockid), sizeof(*this->get_sockaddr(sockid)));
}

