#include "game_screen.hpp"

#include "character.hpp"
#include "debug_graphics.hpp"

#include <GL/gl.h>
#include <SDL/SDL.h>

namespace monomi {
    GameScreen::GameScreen() :
        quit_(false),
        cameraScale_(5.0f),
        debugGraphics_(new DebugGraphics),
        playerCharacter_(new Character)
    { }

    GameScreen::~GameScreen()
    { }
    
    std::auto_ptr<Screen> GameScreen::run()
    {
        do {
            pumpEvents();
            draw();
        } while (!quit_);
        return std::auto_ptr<Screen>();
    }

    void GameScreen::pumpEvents()
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

    void GameScreen::draw()
    {
        // Set up camera.
        SDL_Surface *videoSurface = SDL_GetVideoSurface();
        float aspectRatio = (float(videoSurface->w) /
                             float(videoSurface->h));
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(cameraPosition_.x - cameraScale_ * aspectRatio,
                cameraPosition_.x + cameraScale_ * aspectRatio,
                cameraPosition_.y - cameraScale_,
                cameraPosition_.y + cameraScale_,
                -1.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);

        // Draw.
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
                GL_STENCIL_BUFFER_BIT);
        playerCharacter_->debugDraw(debugGraphics_.get());
        SDL_GL_SwapBuffers();
    }
}
