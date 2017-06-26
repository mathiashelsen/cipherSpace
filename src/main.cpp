#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "util/serverSide.hpp"
#include <sys/wait.h>

void echoPlusOne(
    void *args, // Arguments that the user can specify
    char *msg,  // Message received by the server
    serverSide *server);

int main(int argc, char **argv)
{
    bool looping = true;
    serverSide myServer = serverSide(atoi(argv[1]), &echoPlusOne);
    myServer.start();

    printf("Server initialized successfully.\n Please enter command\n ");

    while(looping)
    {
        printf("    > ");
        char command = 0;
        scanf("%c", &command);

        switch(command)
        {
            case 'c':
                printf("Going to connect\n");
                break;
            case 'q':
                printf("Going to quit\n");
                looping = false;
                break;
            default:
                // None
                break;
        }
    }
    
    
    myServer.terminate();

    while( wait(0) != -1);
    printf("Done waiting, exiting\n");
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
