#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "util/serverSide.hpp"

void echoPlusOne(
    void *args, // Arguments that the user can specify
    char *msg,  // Message received by the server
    serverSide *server);

int main(int argc, char **argv)
{
    serverSide myServer = serverSide(atoi(argv[1]), &echoPlusOne);
    myServer.start();

    wait();

    return(0);
}

void echoPlusOne(
    void *args, // Arguments that the user can specify
    char *msg,  // Message received by the server
    serverSide *server)
{
    printf("Received message: \n\t%s\n", msg);
    char newMsg[255];
    bzero( newMsg, 255 );
    memcpy(newMsg, msg, 255);
   
    int i = 0;
    while(newMsg[i] != 0)
    {
        newMsg[i] = newMsg[i]+1;
        i++;
    } 
    printf("Going to send message: %s\n", newMsg);
    server->sendMessage(newMsg);
}
