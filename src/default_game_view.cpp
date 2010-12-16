#include "default_game_view.hpp"

namespace monomi {
    DefaultGameView::DefaultGameView(GamePtr const &game) :
        game_(game)
    { }

    bool DefaultGameView::alive() const
    {
        return true;
    }

    void DefaultGameView::update(float dt)
    {
    }
}
