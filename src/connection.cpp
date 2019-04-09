#include "connection.h"
#include "secure_queue.h"

void * service(void * arg) {
    connection * con = static_cast<connection *>(arg);
    char buff[MAX_LEN_INPUT_STR];
    int lenght = 0;
    while(1) {
        std::cout << con->get_id() << std::endl;
        while (con->out.empty() == false) {
            int error = 0;
            socklen_t len = sizeof (error);
            int retval = getsockopt(con->sock_fd, SOL_SOCKET, SO_ERROR, &error, &len);
            if (error != 0) {
                std::cout << "sock err\n";
                return nullptr;
            }
            int l = send(con->sock_fd, con->out.front().get_str().c_str(), strlen(con->out.front().get_str().c_str()), 0);
            std::cout << "l:" << l << std::endl;
            if (l < 1 ) {
                std::cout << "send err\n";
                return nullptr;
            }   
            con->out.pop();
        }
        while (lenght = recv(con->sock_fd, buff, MAX_LEN_INPUT_STR, MSG_WAITALL) > 0) {
            con->in.push(message(con->id, std::string(buff)));
        }
        if (lenght < 0) {
            std::cerr << "error input on socket " << con->sock_fd << " on client with id " << con->id << std::endl;
            return nullptr;
        }
    }
}

connection::connection(int sock, int in_id) {
    sock_fd = sock;
    fcntl(sock_fd, F_SETFL, O_NONBLOCK);
    id = in_id;
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
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
    return a.get_id() < b.get_id();
}

const bool operator > (const connection & a, const connection & b) {
    return a.get_id() > b.get_id();
}

const bool operator == (const connection & a, const connection & b) {
    return a.get_id() == b.get_id();
}

int connection::get_id() const {
    return id;
}


