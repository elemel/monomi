#ifndef MONOMI_GAME_SCREEN_HPP
#define MONOMI_GAME_SCREEN_HPP

#include "screen.hpp"

#include <memory>
#include <boost/noncopyable.hpp>

namespace monomi {
    class GameEngine;
    class Window;

    class GameScreen :
        public Screen,
        private boost::noncopyable
    {
    public:
        explicit GameScreen(Window *window);

        bool alive();

        void update();
        void draw();

        void onOpen();
        void onSuspend();
        void onResume();
        void onClose();

        void onKeyPress(Key key, Modifiers modifiers);
        void onKeyRelease(Key key, Modifiers modifiers);

    private:
        Window *window_;
        bool alive_;
        std::auto_ptr<GameEngine> gameEngine_;
    };
}

#endif // MONOMI_GAME_SCREEN_HPP
