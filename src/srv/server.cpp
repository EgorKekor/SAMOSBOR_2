#include "server.h"
server::~server() {
    for(std::map<int, connection*>::iterator i = connects.begin(); i != connects.end(); i++) {
        if (i->second != nullptr) {
            delete i->second;
        }
    }
}

void server::push(message msg) {
    to_clients.push(msg);
    sem_post(&(dist_semaphore));
}

void server::push(std::vector<message> &msg) {
    to_clients.push(msg);
    sem_post(&(dist_semaphore));
}

bool server::empty() {
    return to_server.empty();
}

void server::pop() {
    return to_server.pop();
}

message server::front() {
    return to_server.front();
}

void server::lock() {
    connects_mutex.lock();
}

void server::unlock() {
    connects_mutex.unlock();
}

void * find_client(void * arg) {
    server * srv = static_cast<server*>(arg);
    static int current_new_id = MIN_ID;
    struct sockaddr_in new_client_address;
    int new_sock_fd;
    while(1) {
        socklen_t sock_size = sizeof(new_client_address);

        std::cout << "жду нового бойца в клуб!\n";
        new_sock_fd = accept(srv->in_sock_fd, (struct sockaddr*)&new_client_address, &sock_size);
        std::cout << "ебать, новый чувак пришел поиграть\n";
        srv->lock();
        connection *conn = new connection(new_sock_fd, current_new_id);
        auto p = std::pair<int, connection*>(current_new_id, conn);
        srv->connects.insert(p);
        srv->unlock();
        current_new_id++;
    }
}

void * distribution(void * arg) {
    server * srv = static_cast<server*>(arg);
    while(1) {
        srv->lock();
        start_connects_iteration:
        for(auto i = srv->connects.begin(); i != srv->connects.end(); i++) {
            while (i->second->empty() == false) {
                if (i->second->front().flag() & CONNECTION_ABORTED) {
                    i->second->get_message();
                    delete i->second;
                    srv->connects.erase(i);
                    std::cout << "delete connection\n";
                    goto start_connects_iteration;
                }
                srv->to_server.push(i->second->get_message());
            }
        }
        srv->unlock();
        while(srv->to_clients.empty() == false) {
            message mes = srv->to_clients.front();
            srv->to_clients.pop();
            if (mes.id() == MULTICAST_ID) {

                srv->lock();
                for(auto i = srv->connects.begin(); i != srv->connects.end(); i++) {
                    std::cout << mes.flag() << " " << mes.id()<< " is multi\n";
                    i->second->push(mes);
                }
                srv->unlock();
            } else {
                srv->lock();
                if (srv->connects.find(mes.id()) != srv->connects.end()) {
                    srv->connects[mes.id()]->push(mes);
                }
                srv->unlock();
            }
        }
        ///sem_wait(&(srv->dist_semaphore)); ????
    }
}

server::server() {
    in_sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&my_address, 0, sizeof(my_address));
    my_address.sin_family = AF_INET;
    my_address.sin_addr.s_addr = htonl(INADDR_ANY);
    my_address.sin_port = htons(PORT);
    bind(in_sock_fd, (struct sockaddr *)&my_address, sizeof(my_address));
    listen(in_sock_fd, MAX_CLIENTS_QUEUE);
    sem_init(&dist_semaphore, 0, 1);
    pthread_create(&new_client_listen, NULL, find_client, static_cast<void*>(this));
    pthread_create(&distributor, NULL, distribution, static_cast<void*>(this));
}

