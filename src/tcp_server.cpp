#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <queue>
#include <vector>
#include <string>
#include <iostream>

#define PORT	1100
#define MAX_CLIENTS_QUEUE 5
#define MAX_LEN_INPUT_STR 8192
#define CONNECT -1
#define MIN_ID 1 // must be bigger then MULTICAST_ID
#define MULTICAST_ID 0

struct message {
    int id;
    int mes;
    message(int id_arg, int mes_arg):
        id(id_arg), mes(mes_arg){;};
    message() {;};
};

struct client {
        int sock_fd;
        int id;
        client(int sock_fd_arg, int id_arg): 
            sock_fd(sock_fd_arg), id(id_arg){;};
    };

class Server {
 public:
    Server(std::queue<message> *, std::queue<message> *);
    ~Server(){;};
 private:
    std::queue<message> * to_clients;
    std::queue<message> * to_server;
    int in_sock_fd;
    struct sockaddr_in my_address;

    pthread_t new_client_listen;
    pthread_t sending_messages;
    pthread_t listen_messages;

    friend void * find_client(void *);
    std::vector<client> clients;
    friend void * sending_out(void *);
    friend void * listen_in(void *);
};

void * sending_out(void * arg) {
    Server * server = static_cast<Server *>(arg);
    message current_message;
    std::string out_string;
    while(1) {
        if (server -> to_clients -> empty()) {
            //usleep(1000);
            continue;

        }
        current_message = server -> to_clients -> front();
        if (current_message.id == MULTICAST_ID) {
            for (int i = 0; i < server -> clients.size(); i++) {
                //there we must parse protobuf struct to string and send string
                if (current_message.mes % 2 == 0) {
                    send(server -> clients[i].sock_fd, "multicast message % 2 == 0", strlen("multicast message % 2 == 0"), 0);
                } else {
                    send(server -> clients[i].sock_fd, "multicast message % 2 == 1", strlen("multicast message % 2 == 1"), 0);
                }
            }
        } else {  //message to a specific client
            for (int i = 0; i < server -> clients.size(); i++) {
                //there we must parse protobuf struct to string and send string
                if (current_message.id == server -> clients[i].id) {
                    for (int j = 0; j < current_message.mes; j++){
                        send(server -> clients[i].sock_fd, "your specific message", strlen("your specific message"), 0);
                    }
                }
            }
        }
        server -> to_clients -> pop();
    }
}

void * listen_in(void * arg) {
    Server * server = static_cast<Server *>(arg);
    char buff[MAX_LEN_INPUT_STR];
    std::string str;
    while(1) {
        for(int i = 0; i < server -> clients.size(); i++) {
            int lenght = recv(server -> clients[i].sock_fd, buff, MAX_LEN_INPUT_STR, 0);
            if (lenght < 0) {
                std::cerr << "error input on socket " << server -> clients[i].sock_fd << " on client with id " << server -> clients[i].id << std::endl;
            }
            buff[lenght] = '\0';
            server -> to_server -> push(message(server -> clients[i].id, strlen(buff)));
        }
    }
}

void * find_client(void * arg) {
    std::cout << "i am here\n";
    Server * server = static_cast<Server *>(arg);
    static int current_new_id = MIN_ID;
    struct sockaddr_in new_client_address;
    int new_sock_fd;
    while(1) {
        socklen_t sock_size = sizeof(new_client_address);
        new_sock_fd = accept(server -> in_sock_fd, (struct sockaddr*)&new_client_address, &sock_size);
        fcntl(new_sock_fd, F_SETFL, O_NONBLOCK);
        server -> clients.push_back(client(new_sock_fd, current_new_id));
        server -> to_server -> push(message(current_new_id, CONNECT));
        current_new_id++;
    }
}

Server::Server(std::queue<message> * arg_to_clients, std::queue<message> * arg_to_server) {
    to_clients = arg_to_clients;
    to_server = arg_to_server;
    in_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&my_address, 0, sizeof(my_address));
    my_address.sin_family = AF_INET;
    my_address.sin_addr.s_addr = htonl(INADDR_ANY);
    my_address.sin_port = htons(PORT);
    bind(in_sock_fd, (struct sockaddr *)&my_address, sizeof(my_address));
    listen(in_sock_fd, MAX_CLIENTS_QUEUE);
    pthread_create(&new_client_listen, NULL, find_client, static_cast<void*>(this));
    pthread_create(&new_client_listen, NULL, listen_in, static_cast<void*>(this));
    pthread_create(&new_client_listen, NULL, sending_out, static_cast<void*>(this));


}
int main() {
    std::queue<message> in, out;
    Server a(&in, &out);
    sleep(100);
}
