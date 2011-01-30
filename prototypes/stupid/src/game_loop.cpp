#include "game_loop.hpp"

#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>

namespace monomi {
    GameLoop::GameLoop() :
        quit_(false)
    { }

    void GameLoop::run()
    {
        while (!quit_) {
            handleInput();
            updateLogic();
            updateView();
        }
    }

    void GameLoop::handleInput()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit_ = true;
                }
                break;
    
            case SDL_KEYUP:
                break;
    
            case SDL_QUIT:
                quit_ = true;
                break;
            }
        }
    }

    void GameLoop::updateLogic()
    {
    }

    void GameLoop::updateView()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_GL_SwapBuffers();
    }
}
