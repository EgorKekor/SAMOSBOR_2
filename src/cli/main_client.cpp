#include <iostream>
#include <SFML/Graphics.hpp>

#include "client.h"

int main() {
    client a;
    std::string adr;
    std::cin >> adr;
    while (a.connect_to_address(adr) != 0) {
        std::cout << "error addres\n";
        std::cin >> adr;
    }
    std::cout << "connected\n";
    sleep(100);
    sf::RenderWindow window(sf::VideoMode(640, 480), "Samosbor");

  return 0;
}
