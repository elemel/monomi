#ifndef MONOMI_GAME_APPLICATION_HPP
#define MONOMI_GAME_APPLICATION_HPP

#include "game.hpp"
#include "game_view.hpp"

#include <vector>
#include <boost/noncopyable.hpp>

namespace monomi {
    class GameApplication;

    typedef boost::shared_ptr<GameApplication> GameApplicationPtr;
    typedef boost::weak_ptr<GameApplication> GameApplicationWeakPtr;

    class GameApplication :
        private boost::noncopyable
    {
    public:
        GameApplication();

        void run();

    private:
        typedef std::vector<GameViewPtr> ViewVector;

        float dt_;
        GamePtr game_;
        ViewVector gameViews_;
    };
}

#endif // MONOMI_GAME_APPLICATION_HPP
