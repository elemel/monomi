#ifndef MONOMI_SDL_WINDOW_HPP
#define MONOMI_SDL_WINDOW_HPP

#include "window.hpp"

struct SDL_Surface;

namespace monomi {
    class SDLWindow : public Window {
    public:
        SDLWindow();
        virtual ~SDLWindow();

        virtual void run();
    
    private:
        SDL_Surface *videoSurface_;

        void handleEvents();
    };
}

#endif // MONOMI_SDL_WINDOW_HPP
