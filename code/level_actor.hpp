#ifndef MONOMI_LEVEL_ACTOR_HPP
#define MONOMI_LEVEL_ACTOR_HPP

#include "actor.hpp"

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>

namespace monomi {
    class GameEngine;

    class LevelActor :
        public Actor,
        private boost::noncopyable
    {
    public:
        LevelActor(GameEngine *gameEngine,
                   const std::vector<std::string> &lines);

        bool alive();

        void step(float dt);
        void debugDraw(DebugGraphics *debugGraphics);

    private:
        GameEngine *gameEngine_;
        std::vector<std::vector<char> > tiles_;
    };
}

#endif // MONOMI_LEVEL_ACTOR_HPP
