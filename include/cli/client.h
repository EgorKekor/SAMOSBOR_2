#ifndef SERVER_H
#define SERVER_H
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <utility>

#include "res/message.h"
#include "res/secure_queue.h"
#include "res/connection.h"


#define PORT 1106

class client {
 public:
    client();
    ~client();
    void push(message);
    const message& front();
    std::vector<message> GetInput();
    void pop();
    bool empty();
    int connect_to_address(const std::string&);
 private:
    int sock_fd;
    struct sockaddr_in my_address;
    secure_queue<message> to_server;
    connection * server_connection;
};

#endif
