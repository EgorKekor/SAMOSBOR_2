//
// Created by kekor on 19.05.19.
//

#include "res/TextureManager.h"

TextureManager::TextureManager() : Player(44, 71){
    UnitsTextures.emplace_back(std::vector<sf::Texture>());

    sf::Texture main;
    main.loadFromFile("../Graphics/MainHero/Main_walk.png");
    UnitsTextures.back().push_back(main);

    main.loadFromFile("../Graphics//MainHero/Main_shoot_pistol.png");
    UnitsTextures.back().push_back(main);

    main.loadFromFile("../Graphics/MainHero/Main_fight.png");
    UnitsTextures.back().push_back(main);

    main.loadFromFile("../Graphics/MainHero/Main_smert.png");
    UnitsTextures.back().push_back(main);

    Player.actionsAmount = UnitsTextures[Entityes::type::PLAYER].size();

}


void TextureManager::InitPlayer() {
    PlayerSprites.resize(Player.actionsAmount);
    for (size_t action = 0; action < Player.actionsAmount; action++) {
        PlayerSprites[action].resize(Player.dirrectionsAmount);

        for (int dirr = 0; dirr < Player.dirrectionsAmount; dirr++) {
            PlayerSprites[action][dirr].resize(Player.maxViews);
        }
    }

    for (size_t action = 0; action < Player.actionsAmount; action++) {
        for (size_t dirr = 0; dirr < Player.dirrectionsAmount; dirr++) {
            for (size_t view = 0; view < Player.actionsViewsAmount[action]; view++) {
                sf::Sprite sp;
                sp.setTexture(UnitsTextures[Entityes::type::PLAYER][action]);
                sp.setTextureRect(sf::IntRect(view * Player.actionsWidth[action], dirr * Player.actionsHeight[action],
                                              Player.actionsWidth[action], Player.actionsHeight[action]));
                //sp.setPosition(actorParams_.position.x, actorParams_.position.y);
                PlayerSprites[action][dirr][view] = sp;
            }
        }
    }



}


//  ======================================================


void PlayerSize::Init() {
    actionsWidth.resize(actionsAmount);
    actionsHeight.resize(actionsAmount);
    actionsViewsAmount.resize(actionsAmount);

    actionsViewsAmount[Textures::Player::Action::WALK] = 8;         // Количество видов ходьбы
    actionsViewsAmount[Textures::Player::Action::SHOOT] = 5;        // Количество видов выстрела
    actionsViewsAmount[Textures::Player::Action::FIGHT] = 5;        // Количество видов выстрела
    actionsWidth[Textures::Player::Action::WALK] = 44;              // Ширина спрайта ходьбы
    actionsWidth[Textures::Player::Action::SHOOT] = 62;             // Ширина спрайта выстрела
    actionsWidth[Textures::Player::Action::FIGHT] = 57;
    actionsHeight[Textures::Player::Action::WALK] = 70;             // Высота спрайта ходьбы
    actionsHeight[Textures::Player::Action::WALK] = 78;            // Ширина спрайта выстрела
    actionsHeight[Textures::Player::Action::FIGHT] = 70;            // Ширина спрайта выстрела

    maxViews = 8;
    dirrectionsAmount = 6;
}