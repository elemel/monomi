#include "game_engine.hpp"

#include "actor.hpp"

namespace monomi {
    namespace {
        bool dead(const Actor &actor)
        {
            return !actor.alive();
        }
    }

    GameEngine::GameEngine() :
        time_(0.0f)
    { }

    GameEngine::~GameEngine()
    { }

    void GameEngine::addActor(std::auto_ptr<Actor> actor)
    {
        actors_.push_back(actor);
    }

    void GameEngine::step(float dt)
    {
        time_ += dt;
        actors_.erase_if(&dead);
    }

    void GameEngine::draw() const
    { }
}
