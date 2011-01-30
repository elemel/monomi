#include "game_loop.hpp"

#include "debug_graphics.hpp"
#include "game_logic.hpp"

#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>

namespace monomi {
    GameLoop::GameLoop() :
        quit_(false),
        time_(0.0f),
        dt_(1.0f / 60.0f),
        gameLogic_(new GameLogic),
        debugGraphics_(new DebugGraphics)
    { }

    void GameLoop::run()
    {
        time_ = 0.001f * SDL_GetTicks();
        while (!quit_) {
            float time = 0.001f * SDL_GetTicks();
            while (time_ + dt_ <= time) {
                time_ += dt_;
                handleInput();
                updateLogic();
                updateView();
            }
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
        gameLogic_->update(dt_);
    }

    void GameLoop::updateView()
    {
        // Set up camera.
        SDL_Surface *videoSurface = SDL_GetVideoSurface();
        float aspectRatio = (float(videoSurface->w) /
                             float(videoSurface->h));
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float cameraPosition[2] = { 0.0f, 0.0f };
        float cameraScale = 10.0f;
        glOrtho(cameraPosition[0] - cameraScale * aspectRatio,
                cameraPosition[0] + cameraScale * aspectRatio,
                cameraPosition[1] - cameraScale,
                cameraPosition[1] + cameraScale,
                -1.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gameLogic_->debugDraw(debugGraphics_.get());
        SDL_GL_SwapBuffers();
    }
}
