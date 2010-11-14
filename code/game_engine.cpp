#include "game_engine.hpp"

#include "actor.hpp"
#include "gl_debug_graphics.hpp"

#include <GL/gl.h>

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
    { }

    void GameEngine::debugDraw()
    {
        float scale = 2.0f;
        float aspectRatio = float(screenWidth_) / float(screenHeight_);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-scale * aspectRatio, scale * aspectRatio,
                -scale, scale,
                -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);

        GLDebugGraphics debugGraphics;
        glPushMatrix();
        debugGraphics.drawCircle(Circle(Point2(), 1.0f));
        typedef boost::ptr_vector<Actor>::iterator Iterator;
        for (Iterator i = actors_.begin(); i != actors_.end(); ++i) {
            i->debugDraw(&debugGraphics);
        }
    }
}
