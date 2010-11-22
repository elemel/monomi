#ifndef MONOMI_SDL_WINDOW_HPP
#define MONOMI_SDL_WINDOW_HPP

#include "window.hpp"

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

struct SDL_Surface;

namespace monomi {
    class SDLWindow :
        public Window,
        private boost::noncopyable
    {
    public:
        SDLWindow();
        ~SDLWindow();

        int width();
        int height();
        Screen *topScreen();

        void pushScreen(std::auto_ptr<Screen> screen);
        void run();
    
    private:
        SDL_Surface *videoSurface_;
        boost::ptr_vector<Screen> screens_;

        void handleEvents();
    };
}

#endif // MONOMI_SDL_WINDOW_HPP
