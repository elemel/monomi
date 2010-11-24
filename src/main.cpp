#include "title_screen.hpp"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <GL/gl.h>
#include <SDL/SDL.h>

int main(int argc, char *argv[])
{
    try {
        // Initialize SDL.
        if (SDL_Init(SDL_INIT_VIDEO) == -1) {
            std::stringstream message;
            message << "Failed to initialize SDL: " << SDL_GetError();
            throw std::runtime_error(message.str());
        }
        atexit(&SDL_Quit);

        // Set video mode.
        SDL_Surface *videoSurface_ = SDL_SetVideoMode(0, 0, 0, SDL_OPENGL | SDL_FULLSCREEN);
        if (videoSurface_ == 0) {
            std::stringstream message;
            message << "Failed to set SDL video mode: " << SDL_GetError();
            throw std::runtime_error(message.str());
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
