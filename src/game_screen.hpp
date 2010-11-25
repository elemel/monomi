#ifndef MONOMI_GAME_SCREEN_HPP
#define MONOMI_GAME_SCREEN_HPP

#include "screen.hpp"

#include "geometry.hpp"

#include <memory>
#include <boost/ptr_container/ptr_vector.hpp>
#include <SDL/SDL.h>

namespace monomi {
    class Block;
    class Character;
    class DebugGraphics;

    class Camera {
    public:
        Camera();

        Point2 position;
        float scale;
    };

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
        Camera camera_;
        std::auto_ptr<DebugGraphics> debugGraphics_;
        std::auto_ptr<Character> playerCharacter_;
        boost::ptr_vector<Block> blocks_;

        void pumpEvents();
        void onKeyDown(SDL_Event const &event);
        void onKeyUp(SDL_Event const &event);
        void step();
        void resolveCollisions();
        void draw();
    };
}

#endif // MONOMI_GAME_SCREEN_HPP
