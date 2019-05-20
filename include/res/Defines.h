//
// Created by kekor on 18.05.19.
//

#ifndef SERVER_NAMES_H
#define SERVER_NAMES_H

#define MAX_PLAYERS     2

namespace ServerMessages {
    enum flag {MAKE_ENTITY, MAKE_MOVE, MAKE_DAMAGE, MAKE_BULLET, START_GAME};
    enum id {MULTICAST, FIRST = 1, LAST = 2};
}

namespace ClientMessages {
    enum flag {KEY_PRESSED, MOUSE_PRESSED};
    enum key {NUM1=1, NUM2, NUM3, NUM4, W, S, A, D};

}

namespace Textures {
    namespace Player {
        enum Action {WALK, SHOOT, FIGHT, DEAD};
    }

    namespace Npc {

    }

    enum Dirrection {UP, RIGHT, DOWN, LEFT};
}

namespace Weapon {
    enum Gun {HAND, PISTOL, AUTOMAT};
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
