#include "character_actor.hpp"

#include "debug_graphics.hpp"

namespace monomi {
    CharacterControls::CharacterControls() :
        left(false),
        right(false),
        up(false),
        down(false),
        action(false)
    { }

    CharacterActor::CharacterActor(GameEngine *gameEngine, float radius) :
        gameEngine_(gameEngine),
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
