#ifndef _CLIENTSIDE_HPP
#define _CLIENTSIDE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
//#include <mutex>

class clientSide
{
    private:
        int sockfd, portno, n;
        struct sockaddr_in serv_addr;
        struct hostent *server;
    public:
        clientSide(int _portno, 
            char *_hostname
            );
        ~clientSide();
        int sendMessage(char *msg);
        int recvMessage(char *msg, int nBytes);
};

#endif
