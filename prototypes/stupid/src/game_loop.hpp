#ifndef MONOMI_GAME_LOOP
#define MONOMI_GAME_LOOP

#include <boost/shared_ptr.hpp>

union SDL_Event;

namespace monomi {
    class DebugGraphics;
    class GameLogic;

    class GameLoop {
    public:
        GameLoop(boost::shared_ptr<GameLogic> gameLogic);

        void run();

    private:
        bool quit_;
        boost::shared_ptr<GameLogic> gameLogic_;
        boost::shared_ptr<DebugGraphics> debugGraphics_;

        void handleEvents();
        void handleKeyDownEvent(SDL_Event const &event);
        void handleKeyUpEvent(SDL_Event const &event);

        void updateLogic(float dt);
        void updateView(float dt);
    };
}

#endif // MONOMI_GAME_LOOP
