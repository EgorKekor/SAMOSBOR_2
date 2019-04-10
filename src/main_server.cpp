#include "server.h"

int main() {
    server a;
    message msg;
    msg.set_id(0);
    msg.set_flag(312);
    while (1) {
        sleep(1);
        while (a.empty() == false) {
            a.push(a.front());
            a.pop();
        }
        a.push(msg);
        msg.set_flag(312);
    }
}
