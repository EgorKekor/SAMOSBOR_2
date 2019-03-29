#ifndef CONNECT_H
#define CONNECT_H
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <secure_queue.h>
#include <message.h>

#define MAX_LEN_INPUT_STR 8192

class connection {
 public:
    connection(int, int);
    bool empty();
    message get_message();
    void push(message);
    const bool operator < (const connection &);
    const bool operator > (const connection &);
    const bool operator == (const connection &);
    
 private:
    secure_queue<message> in;
    secure_queue<message> out; 
    int sock_fd;
    int id;
    pthread_t thread;
    void * sending_out(void *);
};

#endif
