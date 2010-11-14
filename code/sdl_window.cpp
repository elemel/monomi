#include "sdl_window.hpp"

#include "screen.hpp"

#include <sstream>
#include <stdexcept>
#include <SDL.h>

namespace monomi {
    SDLWindow::SDLWindow() :
        videoSurface_(0)
    {
        SDL_Init(SDL_INIT_VIDEO);

        videoSurface_ = SDL_SetVideoMode(0, 0, 0, SDL_OPENGL | SDL_FULLSCREEN);
        if (videoSurface_ == 0) {
            std::stringstream message;
            message << "Could not set SDL video mode: " << SDL_GetError();
            throw std::runtime_error(message.str());
        }
    }

    SDLWindow::~SDLWindow()
    {
        SDL_Quit();
    }

    int SDLWindow::width()
    {
        return videoSurface_->w;
    }

    int SDLWindow::height()
    {
        return videoSurface_->h;
    }

    Screen *SDLWindow::topScreen()
    {
        return screens_.empty() ? 0 : &screens_.back();
    }

    void SDLWindow::pushScreen(std::auto_ptr<Screen> screen)
    {
        screens_.push_back(screen.release());
    }

    void SDLWindow::run()
    {
        while (!screens_.empty()) {
            handleEvents();
            if (!screens_.empty()) {
                screens_.back().update();
                screens_.back().draw();
                SDL_GL_SwapBuffers();
                while (!screens_.empty() && !screens_.back().alive()) {
                    screens_.pop_back();
                }
            }
        }
    }

    void SDLWindow::handleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                if (topScreen()) {
                    topScreen()->onKeyPress(keys::escape, Modifiers());
                }
                break;

            case SDL_KEYUP:
                if (topScreen()) {
                    topScreen()->onKeyRelease(keys::escape, Modifiers());
                }
                break;

            case SDL_QUIT:
                screens_.clear();
                break;
            }
        }
    }
}
