#ifndef MONOMI_GAME_HPP
#define MONOMI_GAME_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace monomi {
    class Game;

    typedef boost::shared_ptr<Game> GamePtr;
    typedef boost::weak_ptr<Game> GameWeakPtr;

    class Game {
    public:
        void update(float dt);
    };
}

#endif // MONOMI_GAME_HPP
