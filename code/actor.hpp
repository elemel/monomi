#ifndef MONOMI_ACTOR_HPP
#define MONOMI_ACTOR_HPP

namespace monomi {
    class DebugGraphics;
    class GameEngine;

    class Actor {
    public:
        explicit Actor(GameEngine *gameEngine);
        
        virtual ~Actor();

        virtual bool alive() const;

        virtual void step(float dt);
        virtual void draw() const;
        virtual void debugDraw(DebugGraphics *debugGraphics) const;
    
    protected:
        GameEngine *gameEngine_;
        bool alive_;
    };
}

#endif // MONOMI_ACTOR_HPP
