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


#define PORT 1100

class client {
 public:
    client();
    ~client();
    void push(message);
    const message& front();
    void pop();
    bool empty();
    int connect_to_address(std::string);
 private:
    int sock_fd;
    struct sockaddr_in my_address;
    secure_queue<message> to_server;
    connection * server_connection;
};

#endif
