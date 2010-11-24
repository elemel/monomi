#ifndef MONOMI_GAME_SCREEN_HPP
#define MONOMI_GAME_SCREEN_HPP

#include "screen.hpp"

#include "geometry.hpp"

#include <memory>

namespace monomi {
    class Character;
    class DebugGraphics;

    class GameScreen :
        public Screen
    {
    public:
        GameScreen();
        ~GameScreen();

        std::auto_ptr<Screen> run();

    private:
        bool quit_;
        Point2 cameraPosition_;
        float cameraScale_;
        std::auto_ptr<DebugGraphics> debugGraphics_;
        std::auto_ptr<Character> playerCharacter_;

        void pumpEvents();
        void draw();
    };
}

#endif // MONOMI_GAME_SCREEN_HPP
