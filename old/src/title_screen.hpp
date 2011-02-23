#ifndef MONOMI_TITLE_SCREEN_HPP
#define MONOMI_TITLE_SCREEN_HPP

#include "screen.hpp"

#include <SDL.h>

namespace monomi {
    class TitleScreen :
        public Screen
    {
    public:
        TitleScreen();

        std::auto_ptr<Screen> run();

    private:
        bool quit_;

        void pollEvents();
        void onKeyDown(const SDL_Event &event);

        void draw();
    };
}

#endif // MONOMI_TITLE_SCREEN_HPP
