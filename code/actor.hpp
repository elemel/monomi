#ifndef MONOMI_ACTOR_HPP
#define MONOMI_ACTOR_HPP

namespace monomi {
    class DebugGraphics;
    class GameEngine;

    class Actor {
    public:
        explicit Actor(GameEngine *gameEngine);
        
        virtual ~Actor();
    
        virtual void draw();
        virtual void debugDraw(DebugGraphics *debugGraphics);
    
    protected:
        GameEngine *gameEngine_;
    };
}

#endif // MONOMI_ACTOR_HPP
