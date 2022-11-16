#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <netinet/in.h>
#include <vector>

namespace arpis_server {
typedef struct {
    int status;    
    char * buffer;
} arpis_socket_response;

class arpis_socket {
public:
    arpis_socket(int domain, int type, int protocol);    
    void assign_sockaddr(sockaddr_in * sockaddr);  
    int sock_bind(int sockid);
    int get_socket();    
    arpis_socket_response receive(int buf_size, int flags, int sockid);
protected:        
private:    
    int socket_;    
    std::vector<sockaddr_in *> sockaddr_vector_;
};
}

#endif