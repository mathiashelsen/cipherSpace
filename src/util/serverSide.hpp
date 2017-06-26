#ifndef _SERVERSIDE_HPP
#define _SERVERSIDE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
//#include <mutex>

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
        pid_t childPID = 0;
        socklen_t clilen;
        char buffer[256];
        struct sockaddr_in serv_addr, cli_addr;
        int n;
        void *callBackArgs;
        //std::mutex mtx; // To protect the callBackArgs
        void (* callBackFunction)(
            void *args, // Arguments that the user can specify
            char *msg,  // Message received by the server
            serverSide *server);
    public:
        serverSide(int _portno, void (* _callBackFunction)(
            void *args, // Arguments that the user can specify
            char *msg,  // Message received by the server
            serverSide *server) );
        ~serverSide();
        void start();
        int sendMessage(char *msg);
        int recvMessage(char *msg, int nBytes);
        void terminate();
        void setCallBackArgs(void *args) {callBackArgs = args; };
};

#endif
