#ifndef MONOMI_CHARACTER_ACTOR_HPP
#define MONOMI_CHARACTER_ACTOR_HPP

#include "actor.hpp"
#include "geometry.hpp"

#include <boost/noncopyable.hpp>

namespace monomi {
    class GameEngine;

    struct CharacterControls {
        CharacterControls();

        bool left : 1;
        bool right : 1;
        bool up : 1;
        bool down : 1;
        bool action : 1;
    };

    class CharacterActor :
        public Actor,
        private boost::noncopyable
    {
    public:
        CharacterActor(GameEngine *gameEngine, float radius = 0.75f);

        bool alive();

        void step(float dt);
        void debugDraw(DebugGraphics *debugGraphics);

    private:
        GameEngine *gameEngine_;
        float radius_;
        Point2 position_;
        CharacterControls controls_;
    };
}

#endif // MONOMI_CHARACTER_ACTOR_HPP
