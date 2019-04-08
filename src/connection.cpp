#include "connection.h"
#include "secure_queue.h"

void * service(void * arg) {
    connection * con = static_cast<connection *>(arg);
    char buff[MAX_LEN_INPUT_STR];
    int lenght = 0;
    while(1) {
        while (con->out.empty() == false) {
            send(con->sock_fd, "message", strlen("message"), 0);
        }
        
        while (lenght = recv(con->sock_fd, buff, MAX_LEN_INPUT_STR, 0) > 0) {
            if (lenght < 0) {
                std::cerr << "error input on socket " << con->sock_fd << " on client with id " << con->id << std::endl;
            }
            buff[lenght] = '\0';
            con->in.push(message(con->id, std::string(buff)));
        }
    }   
}

connection::connection(int sock, int in_id) {
    sock_fd = sock;
    id = in_id;
    pthread_create(&thread, NULL, service, NULL);
}

bool connection::empty() {
    return in.empty();
}
message connection::get_message() {
    message result = in.front();
    in.pop();
    return result;
}
void connection::push(message msg) {
    out.push(msg);
}

const bool operator < (const connection & a, const connection & b) {
    return a.id < b.id;
}

const bool operator > (const connection & a, const connection & b) {
    return a.id > b.id;
}

const bool operator == (const connection & a, const connection & b) {
    return a.id == b.id;
}




