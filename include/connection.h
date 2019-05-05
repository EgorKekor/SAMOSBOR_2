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
#include <iostream>

#include <secure_queue.h>
#include <message.h>

#define MAX_LEN_INPUT_STR 32
#define MULTICAST_ID 0

class connection {
 public:
    connection(int, int);
    connection() {;};
    bool empty();
    message get_message();
    const message & front();
    void push(message);
    const bool operator < (const connection &);
    const bool operator > (const connection &);
    const bool operator == (const connection &);
    int get_id() const;
   
 private:
    int id;
    friend void * service(void * arg);
    secure_queue<message> in;
    secure_queue<message> out; 
    int sock_fd;
    pthread_t thread;
    void * sending_out(void *);
};

#endif
