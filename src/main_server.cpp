#include "server.h"

int main() {
    server a;
    message msg(MULTICAST_ID, std::string("test_message"));
    while (1) {
        sleep(1);
        while (a.empty() == false) {
            a.push(a.front());
            msg = a.front();
            a.pop();
        }
        a.push(msg);
    }
}
