#include "server.h"
server::~server() {
    for(std::map<int, connection*>::iterator i = connects.begin(); i != connects.end(); i++) {
        delete i->second;
    }
}

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
            if (mes.get_id() == MULTICAST_ID) {
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

