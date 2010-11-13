#include "screen.hpp"
#include "window.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <SDL.h>

namespace monomi {
    Window::Window() :
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

    Window::~Window()
    {
        popAllScreens();
        SDL_Quit();
    }

    void Window::pushScreen(std::auto_ptr<Screen> screen)
    {
        screens_.push_back(screen.release());
    }

    void Window::run()
    {
        while (!screens_.empty()) {
            handleEvents();
            if (!screens_.empty()) {
                screens_.back()->update();
                screens_.back()->draw();
                SDL_GL_SwapBuffers();
                popDeadScreens();
            }
        }
    }

    void Window::handleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                popAllScreens();
                break;

            case SDL_QUIT:
                popAllScreens();
                break;
            }
        }
    }

    void Window::popAllScreens()
    {
        while (!screens_.empty()) {
            delete screens_.back();
            screens_.pop_back();
        }
    }

    void Window::popDeadScreens()
    {
        while (!screens_.empty() && !screens_.back()->alive()) {
            delete screens_.back();
            screens_.pop_back();
        }
    }
}
