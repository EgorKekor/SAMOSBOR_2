#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT	1100
#define MAX_CLIENTS_QUEUE 5

class Server {
 public:
    Server(std::queue<std::string> *, std::queue<std::string> *);
    ~Server();
    int count_client();
    void set_input(std::queue<std::string> &);
    void set_output(std::queue<std::string> &);
 private:
    std::queue<std::string> * to_clients;
    std::queue<std::string> * to_server;
    int in_sock_fd;
    struct sockaddr_in my_address;

    pthread_t new_client_listen;
    pthread_t sending_messages;
    pthread_t listen_messages;

    void find_client();
    std::vector<client> clients_fd;
    void sending_out();
    void listen();

    struct client {
        int sock_fd;
        int id;
        client(int sock_fd_arg, int id_arg): sock_fd(sock_fd_arg),
                id(id_arg){;};
    };
};

void Server::find_client() {
    static int current_new_id = 0;
    struct sockaddr_in new_client_address;
    int new_sock_fd;
    while(1) {
        new_sock_fd = accept(my_sock_fd, (struct sockaddr*)&new_client_address, sizeof(new_client_address));
        fcntl(new_sock_fd, F_SETFL, O_NONBLOCK);
        clients_fd.push_back(client(new_sock_fd, current_new_id));
        to_server->push(); /////!!!!!1
        current_new_id++;
    }

}

Server::Server(std::queue<std::string> * arg_to_clients, std::queue<std::string> * arg_to_server) {
    to_clients = arg_to_clients;
    to_server = arg_to_server;
    count_client = 0;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&my_address, 0, sizeof(my_address));
    my_address.sin_family = AF_INET;
    my_address.sin_addr.s_addr = htonk(INADDR_ANY);
    my_address.sin_port = htons(PORT);
    bind(in_sock_fd, (struct sockaddr *)&my_address, sizeof(my_address));
    listen(my_sock_fd, MAX_CLIENTS_QUEUE);
    pthread_create(&new_client_listen, NULL, find_client, NULL)
}
