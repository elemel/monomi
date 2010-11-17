#ifndef MONOMI_CHARACTER_ACTOR_HPP
#define MONOMI_CHARACTER_ACTOR_HPP

#include "actor.hpp"
#include "geometry.hpp"

#include <boost/noncopyable.hpp>

namespace monomi {
    class CharacterActor :
        public Actor,
        private boost::noncopyable
    {
    public:
        CharacterActor(float radius = 0.75f);

        bool alive();

        void step(float dt);
        void draw();
        void debugDraw(DebugGraphics *debugGraphics);

    private:
        Point2 position_;
        float radius_;
    };
}

#endif // MONOMI_CHARACTER_ACTOR_HPP
