#ifndef MONOMI_GAME_HPP
#define MONOMI_GAME_HPP

#include "game_fwd.hpp"

#include "actor_fwd.hpp"
#include "process.hpp"

#include <vector>

namespace monomi {
    class Game :
        public Process
    {
    public:
        bool alive() const;
        void update(float dt);

    private:
        typedef std::vector<ActorPtr> ActorVector;

        ActorVector actors_;
    };
}

#endif // MONOMI_GAME_HPP
