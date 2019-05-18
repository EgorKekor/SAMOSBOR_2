//
// Created by kekor on 18.05.19.
//

#ifndef SERVER_NAMES_H
#define SERVER_NAMES_H

namespace ServerMessages {
    enum action {MAKE_ENTITY, MAKE_MOVE, MAKE_DAMAGE, MAKE_BULLET, STAR_GAME};
}

namespace ClientMessages {
    enum action {};
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
