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
                //con->in.push(message(con)); push error message to destroy object
                // but we can add bool flag and in distribution destroy object with bool flag
                std::cout << "sock err\n";
                return nullptr;
            }

            std::string out_message;
            con->out.front().SerializeToString(&out_message);
            int bytes_sending = send(con->sock_fd, out_message.c_str(), out_message.length(), 0);
            if (bytes_sending < 1 ) {
                std::cout << "connection closed\n";
                return nullptr;
            }   
            con->out.pop();
        }
        while (lenght = recv(con->sock_fd, buff, MAX_LEN_INPUT_STR, MSG_WAITALL) > 0) {
            std::string in_message(buff);
            message msg;
            msg.ParseFromString(in_message);
            msg.set_id(con->get_id());
            con->in.push(msg);
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


