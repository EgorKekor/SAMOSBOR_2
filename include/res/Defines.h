//
// Created by kekor on 18.05.19.
//

#ifndef SERVER_NAMES_H
#define SERVER_NAMES_H


namespace ServerMessages {
    enum flag {MAKE_ENTITY, MAKE_MOVE, MAKE_DAMAGE, MAKE_BULLET, START_GAME};
    enum id {MULTICAST};
}

namespace ClientMessages {
    enum flag {KEY_PRESSED, MOUSE_PRESSED};
    enum key {NUM1=1, NUM2, NUM3, NUM4, W, S, A, D};

}


namespace Entityes {
    enum type {PLAYER, BULLET, NPC, INTERACTIVE};
    namespace Names{
    enum players {USUAL};
    enum bullets {HAND, AUTOMAT, PISTOL};
    enum Npc {CENTAUR};
    enum Interactive {DOOR};
    }
}

#endif //SERVER_NAMES_H
