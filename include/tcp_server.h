#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAXPACKETSIZE 4096

class Server {
 public:
    int sockfd, pid;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    pthread_t serevet_thread;
    char msg[MAXPACKETSIZE];
    static std::string message;

    void setup(int port);
    std::string receive();

 private:

}






#endif
