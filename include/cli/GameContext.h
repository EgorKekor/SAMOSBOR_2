#ifndef SERVER_GAMECONTEXT_H
#define SERVER_GAMECONTEXT_H

#include <SFML/Graphics.hpp>

#include "TextureHolder.h"
#include "client.h"

class GameContext {
 public:
  explicit GameContext(sf::RenderWindow &wnd);

  sf::RenderWindow *mWindow;
  sf::View view;
  sf::Vector2u windowSize;
  client Client;

  //TextureHolder allUnitsTextures;
  // MusicPlayer music;

};

#endif //SERVER_GAMECONTEXT_H
