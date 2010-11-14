#include "game_engine.hpp"

#include "actor.hpp"
#include "gl_debug_graphics.hpp"

namespace monomi {
    namespace {
        bool dead(Actor &actor)
        {
            return !actor.alive();
        }
    }

    GameEngine::GameEngine(int screenWidth, int screenHeight) :
        screenWidth_(screenWidth),
        screenHeight_(screenHeight),
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

    void GameEngine::draw()
    {
        GLDebugGraphics debugGraphics;
        typedef boost::ptr_vector<Actor>::iterator Iterator;
        for (Iterator i = actors_.begin(); i != actors_.end(); ++i) {
            i->debugDraw(&debugGraphics);
        }
    }
}
