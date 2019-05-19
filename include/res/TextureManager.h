//
// Created by kekor on 19.05.19.
//

#ifndef SERVER_TEXTUREMANAGER_H
#define SERVER_TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <res/Defines.h>

class ObjectSize {
public:
    ObjectSize(size_t w, size_t h) : width(w), height(h) {};

    virtual void Init() = 0;
    size_t actionsAmount;
    size_t dirrectionsAmount;
    size_t maxViews;
    std::vector<size_t> actionsWidth;
    std::vector<size_t> actionsHeight;
    std::vector<size_t> actionsViewsAmount;
    size_t width;
    size_t height;
};

class PlayerSize : public ObjectSize{
public:
    PlayerSize(size_t w, size_t h) : ObjectSize(w, h) {}
    void Init() override;
};



class TextureManager{
public:
    explicit TextureManager();

    const PlayerSize& GetPlayerSize() const {return Player;};
    const std::vector<std::vector<std::vector<sf::Sprite>>>& GetPlayerSprites() const {return PlayerSprites;};
private:
    void InitPlayer();

    PlayerSize Player;
    std::vector<std::vector<std::vector<sf::Sprite>>> PlayerSprites;


    std::vector<std::vector<sf::Texture>> UnitsTextures;
    std::vector<sf::Texture> ItemsTextures;
};








#endif //SERVER_TEXTUREMANAGER_H
