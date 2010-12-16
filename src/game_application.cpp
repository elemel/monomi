#include "default_game_view.hpp"
#include "game_application.hpp"

namespace monomi {
    GameApplication::GameApplication() :
        dt_(1.0f / 60.0f),
        game_(new Game)
    {
        GameViewPtr defaultGameView(new DefaultGameView(game_));
        gameViews_.push_back(defaultGameView);
    }

    void GameApplication::run()
    {
        for (;;) {
        }
    }
}
