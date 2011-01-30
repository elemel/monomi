#include "game_logic.hpp"

namespace monomi {
    GameLogic::GameLogic() :
        time_(0.0f),
        world_(new b2World(b2Vec2(0.0f, 0.0f), true))
    { }

    void GameLogic::update(float dt)
    {
        time_ += dt;
        world_->Step(dt, 10, 10);
    }
}
