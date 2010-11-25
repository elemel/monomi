#ifndef MONOMI_GAME_SCREEN_HPP
#define MONOMI_GAME_SCREEN_HPP

#include "screen.hpp"

#include "geometry.hpp"

#include <memory>
#include <SDL/SDL.h>

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
        float time_;
        float dt_;
        Point2 cameraPosition_;
        float cameraScale_;
        std::auto_ptr<DebugGraphics> debugGraphics_;
        std::auto_ptr<Character> playerCharacter_;

        void pumpEvents();
        void onKeyDown(SDL_Event const &event);
        void onKeyUp(SDL_Event const &event);
        void step();
        void draw();
    };
}

#endif // MONOMI_GAME_SCREEN_HPP
