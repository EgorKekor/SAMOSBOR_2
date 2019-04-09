#include "connection.h"
#include "secure_queue.h"

void * service(void * arg) {
    connection * con = static_cast<connection *>(arg);
    char buff[MAX_LEN_INPUT_STR];
    int lenght = 0;
    while(1) {
//        sleep(1);
        while (con->out.empty() == false) {

            int len = send(con->sock_fd, con->out.front().get_str().c_str(), strlen(con->out.front().get_str().c_str()), 0);
            std::cout << "lengo: " << len << " lenmust: "<< strlen(con->out.front().get_str().c_str()) << std::endl;

            con->out.pop();
        }
        
        while (lenght = recv(con->sock_fd, buff, MAX_LEN_INPUT_STR, 0) > 0) {

            buff[lenght] = '\0';
            con->in.push(message(con->id, std::string(buff)));
            std::cout << buff <<lenght << std::endl;
        }
        if (lenght < 0) {
            std::cerr << "error input on socket " << con->sock_fd << " on client with id " << con->id << std::endl;
        }
    }
}

connection::connection(int sock, int in_id) {
    sock_fd = sock;
    //fcntl(sock_fd, F_SETFL, O_NONBLOCK);
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




