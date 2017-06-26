#include "serverSide.hpp"

serverSide::serverSide(int _portno, 
    void (* _callBackFunction)
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
    callBackFunction = _callBackFunction;
}

serverSide::~serverSide()
{
     close(newsockfd);
     close(sockfd);
}

void serverSide::start(void)
{
    childPID = fork(); //This little piggy will always listen, while we get to do other stuff in this program
    if(childPID == 0)
    {
        while(true)
        {
            listen(sockfd,5);
            clilen = sizeof(cli_addr);
            newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, 
                &clilen);
            pid_t pid = fork(); // This little piggy has to answer to one specific clietn
            if(pid == 0)
            {
                if (newsockfd < 0) 
                    printf("ERROR on accept");
                bzero(buffer,256);
                n = read(newsockfd,buffer,255);
                if (n < 0) printf("ERROR reading from socket");
                //mtx.lock();
                callBackFunction(NULL, buffer, this);
                //mtx.unlock();
                _exit(0);
            }
        }
    }
}

void serverSide::terminate()
{
    kill(childPID, SIGTERM);
}

int serverSide::sendMessage(char *msg)
{
    n = write(newsockfd, msg, strlen(msg));
    if (n < 0) 
         printf("ERROR writing to socket");
    return n;
}
