#ifndef SERVER_H
#define SERVER_H
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <utility>

#include "message.h"
#include "secure_queue.h"
#include "connection.h"

#define PORT	1100
#define MAX_CLIENTS_QUEUE 5
#define CONNECT -1
#define MIN_ID 1 // must be bigger then MULTICAST_ID



class server {
 public:
    server();
    ~server();
    void lock_to_cli();
    void unlock_to_cli();
    void lock_to_serv();
    void unlock_to_serv();
    void push(message);
    void pop();
    message front();
    bool empty();
 private:
    int in_sock_fd;
    struct sockaddr_in my_address;
    secure_queue<message> to_clients;
    secure_queue<message> to_server;
    pthread_t distributor;
    pthread_t new_client_listen;


    friend void * find_client(void *);
    friend void * distribution(void *);
    std::mutex connects_mutex;
    std::map<int, connection *> connects;
};

#endif
