#include "actor.hpp"

namespace monomi {
    Actor::Actor(GameEngine *gameEngine) :
        gameEngine_(gameEngine),
        alive_(true)
    { }

    Actor::~Actor()
    { }

    bool Actor::alive()
    {
        return alive_;
    }

    void Actor::step(float dt)
    { }

    void Actor::draw()
    { }

    void Actor::debugDraw(DebugGraphics *debugGraphics)
    { }
}
