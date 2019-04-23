#include "server.h"

int main() {
    server a;
    message msg;
    msg.set_id(0);
    msg.set_flag(7);
    command * com = msg.add_commands();
    com->set_id(13);
    com = msg.add_commands();
    com->set_id(15);
    int i = 0;
    while (1) {
        i++;
        usleep(1000);
        while (a.empty() == false) {
            a.push(a.front());
            a.pop();
        }
        msg.set_flag(i % 4);
        a.push(msg);
    }
}
