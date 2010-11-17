#include "character_actor.hpp"

#include "debug_graphics.hpp"

namespace monomi {
    CharacterActor::CharacterActor(float radius) :
        radius_(radius)
    { }

    bool CharacterActor::alive()
    {
        return true;
    }

    void CharacterActor::step(float dt)
    { }

    void CharacterActor::draw()
    { }

    void CharacterActor::debugDraw(DebugGraphics *debugGraphics)
    {
        debugGraphics->drawCircle(Circle(position_, radius_));
    }
}
