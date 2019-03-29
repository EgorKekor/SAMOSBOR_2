#include <connection.h>
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
void connection::push(message) {
    out.push(message);
}

const bool operator < (const connection & a) {
    return id < a.id;
}

const bool operator > (const connection & a) {
    return id > a.id;
}

const bool operator == (const connection & a) {
    return id == a.id;
}

void * connection::service(void * arg) {
    char buff[MAX_LEN_INPUT_STR];
    int lenght = 0;
    while(1) {
        while (out.empty() == false) {
            send(sock_fd, "message", strlen("message"), 0);
        }
        
        while (lenght = recv(sock_fd, buff, MAX_LEN_INPUT_STR, 0) > 0) {
            if (lenght < 0) {
                std::cerr << "error input on socket " << sock_fd << " on client with id " << id << std::endl;
            }
            buff[lenght] = '\0';
            in.push(message(id, strlen(buff)));
        }
    }   

}


void * connection::sending_out(void * arg) {
    message current_message;
    std::string out_string;
    while(1) {
        if (to_clients->empty()) {
            //usleep(1000);
            continue;

        }
        current_message = server->to_clients->front();
        if (current_message.id == MULTICAST_ID) {
            for (int i = 0; i < server->clients.size(); i++) {
                //there we must parse protobuf struct to string and send string
                if (current_message.mes % 2 == 0) {
                    send(server->clients[i].sock_fd, "multicast message % 2 == 0", strlen("multicast message % 2 == 0"), 0);
                } else {
                    send(server->clients[i].sock_fd, "multicast message % 2 == 1", strlen("multicast message % 2 == 1"), 0);
               }
            }
        } else {  //message to a specific client
            for (int i = 0; i < server->clients.size(); i++) {
                //there we must parse protobuf struct to string and send string
                if (current_message.id == server->clients[i].id) {
                    for (int j = 0; j < current_message.mes; j++){
                        send(server->clients[i].sock_fd, "your specific message", strlen("your specific message"), 0);
                    }
                }
            }
        }
        server->to_clients->pop();
    }
}

    char buff[MAX_LEN_INPUT_STR];
    std::string str;
    while(1) {
        for(int i = 0; i < server->clients.size(); i++) {
            int lenght = recv(server->clients[i].sock_fd, buff, MAX_LEN_INPUT_STR, 0);
            if (lenght < 0) {
                std::cerr << "error input on socket " << server->clients[i].sock_fd << " on client with id " << server->clients[i].id << std::endl;
            }
            buff[lenght] = '\0';
            server->to_server->push(message(server->clients[i].id, strlen(buff)));
        }
    }
}

