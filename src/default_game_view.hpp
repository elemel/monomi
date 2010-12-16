#ifndef MONOMI_DEFAULT_GAME_VIEW_HPP
#define MONOMI_DEFAULT_GAME_VIEW_HPP

#include "game_fwd.hpp"
#include "game_view.hpp"

namespace monomi {
    class DefaultGameView;

    typedef boost::shared_ptr<DefaultGameView> DefaultGameViewPtr;
    typedef boost::weak_ptr<DefaultGameView> DefaultGameViewWeakPtr;

    class DefaultGameView :
        public GameView
    {
    public:
        explicit DefaultGameView(GamePtr const &game);

        bool alive() const;
        void update(float dt);

    private:
        GamePtr game_;
    };
}

#endif // MONOMI_DEFAULT_GAME_VIEW_HPP
