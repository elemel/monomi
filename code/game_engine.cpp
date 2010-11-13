#include "game_engine.hpp"

namespace monomi {
    GameEngine::GameEngine() :
        time_(0.0f)
    { }
    
    void GameEngine::step(float dt)
    {
        time_ += dt;
    }

    void GameEngine::draw() const
    { }
}
