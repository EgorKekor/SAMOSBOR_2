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


#include <secure_queue.h>
#include <message.h>
#include <connection.h>

#define PORT	1100
#define MAX_CLIENTS_QUEUE 5
#define MAX_LEN_INPUT_STR 8192
#define CONNECT -1
#define MIN_ID 1 // must be bigger then MULTICAST_ID
#define MULTICAST_ID 0



class server {
 public:
    server();
    ~server(){;};
    void lock_to_cli();
    void unlock_to_cli();
    void lock_to_serv();
    void unlock_to_serv();
    void push(message);
    void pop();
    message front();
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

void server::push(message msg) {
    to_clients.push(msg);
}

void server::pop() {
    return to_server.pop();
}

message server::front() {
    return to_server.front();
}

void server::lock_to_cli() {
    to_clients.lock();
}

void server::unlock_to_cli() {
    to_clients.unlock();
}

void server::lock_to_serv() {
    to_server.lock();
}

void server::unlock_to_serv() {
    to_server.unlock();
}

void * find_client(void * arg) {
    server * srv = static_cast<server*>(arg);
    static int current_new_id = MIN_ID;
    struct sockaddr_in new_client_address;
    int new_sock_fd;
    while(1) {
        socklen_t sock_size = sizeof(new_client_address);
        new_sock_fd = accept(srv->in_sock_fd, (struct sockaddr*)&new_client_address, &sock_size);
        fcntl(new_sock_fd, F_SETFL, O_NONBLOCK);
        srv->connects_mutex.lock();
        connection *conn = new connection(new_sock_fd, current_new_id);
        auto p = std::pair<int, connection*>(1, conn);
        srv->connects.insert(p);
        srv->connects_mutex.unlock();
        current_new_id++;
    }
}

void * distribution(void * arg) {
    server * srv = static_cast<server*>(arg);
    while(1) {
        srv->connects_mutex.lock();
        for(std::map<int, connection*>::iterator i = srv->connects.begin(); i != srv->connects.end(); i++) {
            while (i->second->empty() == false) {
                srv->to_server.push(i->second->get_message());
            }
        }
        srv->connects_mutex.unlock();
        while(srv->to_clients.empty() == false) {
            message mes = srv->to_clients.front();
            if (mes.id = MULTICAST_ID) {
                for(std::map<int, connection*>::iterator i = srv->connects.begin(); i != srv->connects.end(); i++) {
                    i->second->push(mes);
                }
            } else {
                srv->connects[mes.id]->push(mes);
            }
        }
    }
}

server::server() {
    in_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&my_address, 0, sizeof(my_address));
    my_address.sin_family = AF_INET;
    my_address.sin_addr.s_addr = htonl(INADDR_ANY);
    my_address.sin_port = htons(PORT);
    bind(in_sock_fd, (struct sockaddr *)&my_address, sizeof(my_address));
    listen(in_sock_fd, MAX_CLIENTS_QUEUE);
    pthread_create(&new_client_listen, NULL, find_client, static_cast<void*>(this));
    pthread_create(&distributor, NULL, distribution, static_cast<void*>(this));
}

int main() {
    server a();
    sleep(100);
}
