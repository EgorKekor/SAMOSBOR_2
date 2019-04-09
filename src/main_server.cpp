#include "server.h"

int main() {
    server a;
    while (1) {
        if (a.empty() == false) {
            std::cout << "main" << std::endl;
            std::cout << a.front().get_str();
            a.push(a.front());
            a.pop();
        }


    }
}
