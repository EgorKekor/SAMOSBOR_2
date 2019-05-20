#include "res/connection.h"
#include "res/secure_queue.h"

std::vector<message> connection::get_msg_vector() {
    return in.get_all();
}

void connection::leave() {
    std::cout << "somebody leave con thread\n";
    if (actual) {
        actual = false;
    } else {
        message msg;
        msg.set_flag(CONNECTION_ABORTED);
        msg.set_id(get_id());
        in.push(msg);
        out.push(msg);
    }
}

void * listening(void * arg) {
    auto * con = static_cast<connection *>(arg);
    char buff[MAX_LEN_INPUT_STR];
    int lenght = 0;
    message msg;
    while (true) {
        lenght = recv(con->sock_fd, buff, MAX_LEN_INPUT_STR, 0);//MSG_WAITALL);
        if (lenght <= 0) {
            std::cerr << "error input on socket" << con->id << std::endl;
            con->leave();
            return nullptr;
        }
        std::string in_message(buff);
        msg.ParseFromString(in_message);
        msg.set_id(con->get_id());
        con->in.push(msg);        
        if (!con->actual) {
            con->leave();
            std::cout << "end listening\n";
            return nullptr;
        }
    }
}

void pipe(int signal) {
    if (signal != SIGPIPE) {
        std::cout << "error signal\n";
    }
    std::cout << "signal is SIGPIPE\n";
}

void * sending(void * arg) {
    auto * con = static_cast<connection *>(arg);
    signal(SIGPIPE, pipe);
    while(true) {
        std::cout << "s\n";
        int error = 0;
        socklen_t len = sizeof (error);
        int retval = getsockopt(con->sock_fd, SOL_SOCKET, SO_ERROR, &error, &len);
        if (error != 0 || retval != 0) {
            std::cout << "sock closed\n";
            con->leave();
            return nullptr;
        }
        while (!con->out.empty()) {
            std::string out_message;
            con->out.front().SerializeToString(&out_message);
            std::cout << con->out.front().flag() << " is out flag\n" << out_message.c_str() << std::endl;
            con->out.pop();
            int bytes_sending = send(con->sock_fd, out_message.c_str(), out_message.length(), 0);
            if (bytes_sending < 1) {
                con->leave();
                std::cout << "connection closed\n";
                return nullptr;
            }   
        }
        if (!con->actual) {
            con->leave();
            std::cout << "end sending\n";
            return nullptr;
        }
        sem_wait(&(con->semaphore));
    }
}

connection::connection(int sock, int in_id) {
    actual = true;
    sock_fd = sock;
    id = in_id;
    struct timeval tv{};
    tv.tv_sec = 300;
    tv.tv_usec = 0;
    sem_init(&semaphore, 0, 1);
    setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
    pthread_create(&listen_thread, nullptr, listening, static_cast<void*>(this));
    pthread_create(&send_thread, nullptr, sending, static_cast<void*>(this));
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
    sem_post(&semaphore);
}

bool operator < (const connection & a, const connection & b) {
    return a.get_id() < b.get_id();
}

bool operator > (const connection & a, const connection & b) {
    return a.get_id() > b.get_id();
}

bool operator == (const connection & a, const connection & b) {
    return a.get_id() == b.get_id();
}

int connection::get_id() const {
    return id;
}


