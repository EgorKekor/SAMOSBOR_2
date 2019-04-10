#include "connection.h"
#include "secure_queue.h"

void * listening(void * arg) {
    connection * con = static_cast<connection *>(arg);
    char buff[MAX_LEN_INPUT_STR];
    int lenght = 0;
    message msg;
    while (1) {
        lenght = recv(con->sock_fd, buff, MAX_LEN_INPUT_STR, 0);//MSG_WAITALL);
        if (lenght <= 0) {
            msg.set_flag(CONNECTION_ABORTED);
            msg.set_id(con->get_id());
            con->in.push(msg);
            con->out.push(msg);
            std::cerr << "error input on socket" << con->id << std::endl;
            return nullptr;
        }
        std::string in_message(buff);
        msg.ParseFromString(in_message);
        msg.set_id(con->get_id());
        con->in.push(msg);        
        if (con->actual == false) {
            msg.set_flag(CONNECTION_ABORTED);
            msg.set_id(con->get_id());
            con->in.push(msg);
            con->out.push(msg);
            std::cout << "end listening\n";
            return nullptr;
        }
    }
}

void * sending(void * arg) {
    connection * con = static_cast<connection *>(arg);
    while(1) {
        int error = 0;
        socklen_t len = sizeof (error);
        int retval = getsockopt(con->sock_fd, SOL_SOCKET, SO_ERROR, &error, &len);
        if (error != 0 || retval != 0) {
            std::cout << "sock closed\n";
            con->actual = false;
            return nullptr;
        }
        while (con->out.empty() == false) {
            std::string out_message;
            con->out.front().SerializeToString(&out_message);
            con->out.pop();
            int bytes_sending = send(con->sock_fd, out_message.c_str(), out_message.length(), 0);
            if (bytes_sending < 1) {
                std::cout << "connection closed\n";
                return nullptr;
            }   
        }
    }
}

connection::connection(int sock, int in_id) {
    actual = true;
    sock_fd = sock;
    //fcntl(sock_fd, F_SETFL, O_NONBLOCK);
    id = in_id;
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
    pthread_create(&listen_thread, NULL, listening, static_cast<void*>(this));
    pthread_create(&send_thread, NULL, sending, static_cast<void*>(this));
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


