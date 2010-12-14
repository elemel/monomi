#ifndef MONOMI_GAME_VIEW_HPP
#define MONOMI_GAME_VIEW_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace monomi {
    class GameView;

    typedef boost::shared_ptr<GameView> GameViewPtr;
    typedef boost::weak_ptr<GameView> GameViewWeakPtr;

    class GameView {
    public:
        virtual ~GameView()
        { }

        virtual void update(float dt) = 0;
    };
}

#endif // MONOMI_GAME_VIEW_HPP
