#ifndef MONOMI_ACTOR_HPP
#define MONOMI_ACTOR_HPP

#include <boost/noncopyable.hpp>

namespace monomi {
    class DebugGraphics;
    class GameEngine;

    class Actor : private boost::noncopyable {
    public:
        explicit Actor(GameEngine *gameEngine);
        
        virtual ~Actor();

        virtual bool alive();

        virtual void step(float dt);
        virtual void draw();
        virtual void debugDraw(DebugGraphics *debugGraphics);
    
    protected:
        GameEngine *gameEngine_;
        bool alive_;
    };
}

#endif // MONOMI_ACTOR_HPP
