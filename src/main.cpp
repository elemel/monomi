#include "title_screen.hpp"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <GL/gl.h>
#include <SDL.h>

struct ScopedQuit {
    ~ScopedQuit()
    {
        SDL_Quit();
    }
};

int main(int argc, char *argv[])
{
    try {
        // Initialize SDL.
        if (SDL_Init(SDL_INIT_VIDEO) == -1) {
            std::stringstream message;
            message << "Failed to initialize video system: " << SDL_GetError();
            throw std::runtime_error(message.str());
        }
        ScopedQuit scopedQuit;

        // Set video mode.
        if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) == -1) {
            std::cerr << "WARNING: Failed to enable double buffering: "
                      << SDL_GetError() << std::endl;
        }
        SDL_Surface *videoSurface_ = SDL_SetVideoMode(0, 0, 0,
                                                      SDL_OPENGL |
                                                      SDL_FULLSCREEN);
        if (videoSurface_ == 0) {
            std::stringstream message;
            message << "Failed to set video mode: " << SDL_GetError();
            throw std::runtime_error(message.str());
        }
        if (SDL_GL_SetSwapInterval(1) == -1) {
            std::cerr << "WARNING: Failed to enable vertical sync: "
                      << SDL_GetError() << std::endl;
        }

        // Run screens.
        std::auto_ptr<monomi::Screen> screen(new monomi::TitleScreen);
        do {
            screen = screen->run();
        } while (screen.get());

        return 0;
    } catch (const std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }
}
