#ifndef _SERVERSIDE_HPP
#define _SERVERSIDE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <mutex>

/*
 * This will start a server that listens on a specified port.
 * When there is an incoming message, it will execute the callback
 * function on the message.
 * The server will run as a seperate thread.
 */
class serverSide
{
    private:
        int sockfd, newsockfd, portno;
        socklen_t clilen;
        char buffer[256];
        struct sockaddr_in serv_addr, cli_addr;
        int n;
        void *callBackArgs;
        std::mutex mtx; // To protect the callBackArgs
    public:
        serverSide(int portno, void (* callbackFunction)(
            void *args, // Arguments that the user can specify
            char *msg,  // Message received by the server
            serverSide *server) );
        ~serverSide();
        int start();
        int readMsg(int nBytes, char *msg);
        int writeMsg(char *msg);
};

#endif
