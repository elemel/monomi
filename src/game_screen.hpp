#ifndef MONOMI_GAME_SCREEN_HPP
#define MONOMI_GAME_SCREEN_HPP

#include "camera.hpp"
#include "geometry.hpp"
#include "screen.hpp"

#include <SDL.h>
#include <vector>

namespace monomi {
    class Block;
    class Character;
    class CharacterFactory;
    class DebugGraphics;
    class Random;

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
        boost::shared_ptr<Random> random_;
        Camera camera_;
        boost::shared_ptr<DebugGraphics> debugGraphics_;
        boost::shared_ptr<CharacterFactory> characterFactory_;
        std::vector<boost::shared_ptr<Character> > characters_;
        std::vector<boost::shared_ptr<Block> > blocks_;
        LineSegment2 separator_;

        void pumpEvents();
        void onKeyDown(SDL_Event const &event);
        void onKeyUp(SDL_Event const &event);
        void step();
        void performAI();
        void resolveCollisions();
        void resolveBlockCollisions();
        void updateTouchFlags(Character *character);
        void resolveCharacterCollisions();

        void draw();
    };
}

#endif // MONOMI_GAME_SCREEN_HPP
