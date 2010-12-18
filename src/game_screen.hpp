#ifndef MONOMI_GAME_SCREEN_HPP
#define MONOMI_GAME_SCREEN_HPP

#include "camera.hpp"
#include "geometry.hpp"
#include "screen.hpp"

#include <SDL.h>
#include <vector>

namespace monomi {
    class DebugGraphics;
    class Game;

    class GameScreen :
        public Screen
    {
    public:
        GameScreen();
        ~GameScreen();

        boost::shared_ptr<Screen> run();

    private:
        bool quit_;
        float time_;
        float dt_;
        Camera camera_;
        boost::shared_ptr<DebugGraphics> debugGraphics_;
        boost::shared_ptr<Game> game_;

        void pumpEvents();
        void onKeyDown(SDL_Event const &event);
        void onKeyUp(SDL_Event const &event);
        void update();
        void performAI(float dt);

        void draw();
    };
}

#endif // MONOMI_GAME_SCREEN_HPP
