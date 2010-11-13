#include "window.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <GL/gl.h>
#include <SDL.h>

namespace monomi {
    Window::Window(int width, int height) :
        running_(false),
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
        SDL_Quit();
    }

    void Window::run()
    {
        assert(!running_);
        running_ = true;
        while (running_) {
            handleEvents();
        }
    }

    void Window::onResize(int width, int height)
    { }

    void Window::onIdle()
    { }

    void Window::onDraw()
    { }

    void Window::handleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                running_ = false;
                break;

            case SDL_QUIT:
                running_ = false;
                break;
            }
        }
    }
}
