//
// Created by anita on 5/9/19.
//

#ifndef SERVER_TEXTUREHOLDER_H
#define SERVER_TEXTUREHOLDER_H

#include <SFML/Graphics.hpp>

class TextureHolder {
 public:
  explicit TextureHolder();
 private:
  std::vector<std::vector<sf::Texture>> UnitsTextures;
  std::vector<sf::Texture> ItemsTextures;
};

#endif //SERVER_TEXTUREHOLDER_H
