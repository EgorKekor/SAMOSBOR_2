#include "client.h"
void client::pop() {
    server_connection->get_message();
}

const message& client::front() {
    return server_connection->front();
}

void client::push(message msg) {
    server_connection->push(msg);
}

client::~client() {
    if (server_connection != nullptr) {
        delete server_connection;
    }
}

client::client() {
    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_fd == -1) {
        std::cerr << "can`t cteate socket" << std::endl;
    }
    memset(&my_address, 0, sizeof(my_address));
    my_address.sin_family = AF_INET;
    my_address.sin_port = htons(PORT);
    int res = inet_pton(AF_INET, "127.0.0.1", &my_address.sin_addr);
    if (res <= 0) {
        std::cerr << "error of ip:" << res << std::endl;
    }
    res = connect(sock_fd, (struct sockaddr *)&my_address, sizeof(my_address));
    if (res == -1) {
        std::cerr << "connection error" << std::endl;
    }

    server_connection = new connection(sock_fd, 0);
    std::cout << "constructor " << std::endl;
}
