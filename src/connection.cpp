#include "connection.h"
#include "secure_queue.h"

#include <errno.h>
//#define EDOM
//#define EILSEQ
//#define ERANGE
extern int errno;

void * service(void * arg) {
    connection * con = static_cast<connection *>(arg);
    char buff[MAX_LEN_INPUT_STR];
    int lenght = 0;
    while(1) {
        while (con->out.empty() == false) {
            send(con->sock_fd, con->out.front().get_str().c_str(), strlen(con->out.front().get_str().c_str()), 0);
            con->out.pop();
        }
        while (lenght = recv(con->sock_fd, buff, MAX_LEN_INPUT_STR, MSG_WAITALL) > 0) {
            con->in.push(message(con->id, std::string(buff)));
        }
        if (lenght <= 0 && errno != EAGAIN) {
            std::cerr << "error input on socket " << con->sock_fd << " on client with id " << con->id << std::endl;
            return nullptr;
        }
    }
}

connection::connection(int sock, int in_id) {
    sock_fd = sock;
    fcntl(sock_fd, F_SETFL, O_NONBLOCK);
    id = in_id;
    pthread_create(&thread, NULL, service, static_cast<void*>(this));
}

bool connection::empty() {
    return in.empty();
}
message connection::get_message() {
    message result = in.front();
    in.pop();
    return result;
}

const message & connection::front() {
    return in.front();
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




