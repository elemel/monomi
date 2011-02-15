#include "game_loop.hpp"

#include "character_actor.hpp"
#include "debug_graphics.hpp"
#include "game_logic.hpp"
#include "geometry.hpp"

#include <SDL.h>
#include <SDL_opengl.h>

#include <cassert>
#include <iostream>

namespace monomi {
    GameLoop::GameLoop(boost::shared_ptr<GameLogic> gameLogic) :
        quit_(false),
        gameLogic_(gameLogic),
        debugGraphics_(new DebugGraphics)
    { }

    void GameLoop::run()
    {
        float dt = 1.0f / 60.0f;
        float t1 = 0.001f * SDL_GetTicks();
        while (!quit_) {
            float t2 = 0.001f * SDL_GetTicks();

            // Skip frames to avoid becoming unresponsive.
            if (t2 - t1 >= 10.0f * dt) {
                int skip = int((t2 - t1) / dt);
                t1 += float(skip) * dt;
                std::cerr << "WARNING: Skipped " << skip << " frame(s)." << std::endl;
            }
            assert(t2 - t1 <= 10.0f * dt);

            while (t2 - t1 >= dt) {
                t1 += dt;
                handleInput();
                updateLogic(dt);
                updateView(dt);
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

    void GameLoop::updateLogic(float dt)
    {
        gameLogic_->update(dt);
    }

    void GameLoop::updateView(float dt)
    {
        (void) dt;

        // Set up camera.
        SDL_Surface *videoSurface = SDL_GetVideoSurface();
        float aspectRatio = (float(videoSurface->w) /
                             float(videoSurface->h));
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        Vector2 cameraPosition;
        if (GameLogic::CharacterPtr character = gameLogic_->playerCharacter()) {
            cameraPosition = character->position();
        }
        float cameraScale = 10.0f;
        glOrtho(cameraPosition.x - cameraScale * aspectRatio,
                cameraPosition.x + cameraScale * aspectRatio,
                cameraPosition.y - cameraScale,
                cameraPosition.y + cameraScale,
                -1.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gameLogic_->debugDraw(debugGraphics_.get());
        SDL_GL_SwapBuffers();
    }
}
