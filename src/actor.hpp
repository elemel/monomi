#ifndef MONOMI_ACTOR_HPP
#define MONOMI_ACTOR_HPP

namespace monomi {
    class DebugGraphics;

    class Actor {
    public:
        virtual ~Actor();

        virtual bool alive() = 0;

        virtual void step(float dt) = 0;
        virtual void debugDraw(DebugGraphics *debugGraphics) = 0;
    };
}

#endif // MONOMI_ACTOR_HPP
