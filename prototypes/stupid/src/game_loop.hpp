#ifndef MONOMI_GAME_LOOP
#define MONOMI_GAME_LOOP

#include <boost/shared_ptr.hpp>

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

        void handleInput();
        void updateLogic(float dt);
        void updateView(float dt);
    };
}

#endif // MONOMI_GAME_LOOP
