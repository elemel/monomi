#include "actor.hpp"

namespace monomi {
    Actor::Actor(GameEngine *gameEngine) :
        gameEngine_(gameEngine)
    { }

    Actor::~Actor()
    { }

    void Actor::step(float dt)
    { }

    void Actor::draw() const
    { }

    void Actor::debugDraw(DebugGraphics *debugGraphics) const
    { }
}
