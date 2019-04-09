#include "server.h"

int main() {
    server a;
    while (1) {
        sleep(1);
        while (a.empty() == false) {
            a.push(a.front());
            a.pop();
        }


    }
}
