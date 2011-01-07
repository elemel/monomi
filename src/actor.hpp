#ifndef MONOMI_ACTOR_HPP
#define MONOMI_ACTOR_HPP

#include "actor_fwd.hpp"

namespace monomi {
    class DebugGraphics;

    // Part of the game logic. An actor can be e.g. a character, a script, or a
    // region.
    class Actor {
    public:
        virtual ~Actor();

        virtual bool alive() const = 0;
        virtual void update(float dt) = 0;
        virtual void handleCollisions() = 0;
        virtual void debugDraw(DebugGraphics *debugGraphics) = 0;
    };
}

#endif // MONOMI_ACTOR_HPP
