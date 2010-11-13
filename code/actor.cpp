#include "actor.hpp"

namespace monomi {
    Actor::Actor(GameEngine *gameEngine) :
        gameEngine_(gameEngine),
        alive_(true)
    { }

    Actor::~Actor()
    { }

    bool Actor::alive() const
    {
        return alive_;
    }

    void Actor::step(float dt)
    { }

    void Actor::draw() const
    { }

    void Actor::debugDraw(DebugGraphics *debugGraphics) const
    { }
}
