#include "serverSide.hpp"

serverSide::serverSide(int _portno, 
    void (* callbackFunction)
    (
        void *args,
        char *msg,
        serverSide *server
    ) 
)
{
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        printf("ERROR opening socket");
    printf("Socket %d\n", sockfd);
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = _portno;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              printf("ERROR on binding");
}

serverSide::~serverSide()
{
     close(newsockfd);
     close(sockfd);
}

void serverSide::start()
{
    int pid = fork();
    if(pid == 0)
    {
        while(True)
        {
            listen(sockfd,5);
            clilen = sizeof(cli_addr);
            pid = fork();
            if(pid == 0)
            {
                newsockfd = accept(sockfd, 
                    (struct sockaddr *) &cli_addr, 
                    &clilen);
                printf("Accepting...\n");
                if (newsockfd < 0) 
                    printf("ERROR on accept");
                bzero(buffer,256);
                n = read(newsockfd,buffer,255);
                if (n < 0) printf("ERROR reading from socket");
                mtx.lock();
                callbackFunction(NULL, buffer, this);
                mtx.unlock();
            }
        }
    }
}
