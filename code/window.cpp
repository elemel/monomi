#include "window.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <GL/gl.h>
#include <SDL.h>

namespace monomi {
    namespace {
        SDL_Surface *screen = 0;
    }
    
    Window::Window(int width, int height)
    {
        SDL_Init(SDL_INIT_VIDEO);
        const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo();
        screen = SDL_SetVideoMode(videoInfo->current_w, videoInfo->current_h, videoInfo->vfmt->BitsPerPixel, SDL_OPENGL | SDL_FULLSCREEN);
        if (screen == 0) {
            std::stringstream message;
            message << "Could not set SDL video mode: " << SDL_GetError();
            throw std::runtime_error(message.str());
        }
    }

    Window::~Window()
    {
        SDL_Quit();
    }

    void Window::run()
    {
        bool done = false;
        while (!done) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_KEYDOWN:
                    done = true;
                    break;

                case SDL_QUIT:
                    done = true;
                    break;
                }
            }
        }
    }

    void Window::onResize(int width, int height)
    { }
}
