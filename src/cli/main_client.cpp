#include <iostream>
#include <SFML/Graphics.hpp>

#include "client.h"

#include "GameEngine.h"

int main() {
  GameEngine game;
  while (game.running()) {
    game.run();
  }
//    client a;
//    std::string adr;
//    std::cin >> adr;
//    while (a.connect_to_address(adr) != 0) {
//        std::cout << "error addres\n";
//        std::cin >> adr;
//    }
//    std::cout << "connected\n";
//    sleep(100);
  return 0;
}
