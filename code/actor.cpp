#include "actor.hpp"

namespace monomi {
    Actor::Actor(GameEngine *gameEngine) :
        gameEngine_(gameEngine)
    { }

    Actor::~Actor()
    { }
    
    void Actor::draw()
    { }

    void Actor::debugDraw(DebugGraphics *debugGraphics)
    { }
}
