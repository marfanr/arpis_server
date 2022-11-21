#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <netinet/in.h>
#include <vector>

namespace arpis_server {
class socket {
public:
    socket(int domain, int type, int protocol);
    int get_socket();        
    int sock_bind(int sockid);
    void register_sockaddr(sockaddr_in * sockaddr);
    sockaddr_in * get_sockaddr(int id);    
protected:        
private:        
    int socket_;   
    std::vector<sockaddr_in * > sockaddr_;
};
}

#endif