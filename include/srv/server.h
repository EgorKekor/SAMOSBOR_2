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
    void lock();
    void unlock();
    secure_queue<message>& GetInput() {return to_clients;};
    secure_queue<message>& GetOutput() {return to_server;};
    void push(message);
    void push(std::vector<message>&);
    void pop();
    std::vector<message> get_msg_vector();
    message front();
    bool empty();
    int GetConnectNumb();
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
    sem_t dist_semaphore;
};

#endif
