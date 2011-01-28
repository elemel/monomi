#include "game_loop.hpp"
#include "stringer.hpp"

#include <SDL.h>

#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace monomi;

int main(int argc, char *argv[])
{
    try {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) == -1) {
            throw std::runtime_error(Stringer() << "Failed to initialize SDL: " << SDL_GetError());
        }
        SDL_Surface *videoSurface = SDL_SetVideoMode(0, 0, 0, SDL_OPENGL | SDL_FULLSCREEN);
        if (videoSurface == 0) {
            throw std::runtime_error(Stringer() << "Failed to set SDL video mode: " << SDL_GetError());
        }

        GameLoop gameLoop;
        gameLoop.run();

        SDL_Quit();
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
