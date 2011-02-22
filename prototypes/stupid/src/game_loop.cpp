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
    namespace {
        CharacterActor::ControlFlag mapKeyToControl(int key)
        {
            switch (key) {
            case SDLK_w:
            case SDLK_UP:
                return CharacterActor::UP_CONTROL;

            case SDLK_a:
            case SDLK_LEFT:
                return CharacterActor::LEFT_CONTROL;

            case SDLK_s:
            case SDLK_DOWN:
                return CharacterActor::DOWN_CONTROL;

            case SDLK_d:
            case SDLK_RIGHT:
                return CharacterActor::RIGHT_CONTROL;

            case SDLK_SPACE:
                return CharacterActor::JUMP_CONTROL;

            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                return CharacterActor::ACTION_CONTROL;

            default:
                return CharacterActor::CONTROL_COUNT;
            }
        }
    }

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
                handleEvents();
                updateLogic(dt);
                updateView(dt);
            }
        }
    }

    void GameLoop::handleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit_ = true;
                } else {
                    handleKeyDownEvent(event);
                }
                break;
    
            case SDL_KEYUP:
                handleKeyUpEvent(event);
                break;
    
            case SDL_QUIT:
                quit_ = true;
                break;
            }
        }
    }

    void GameLoop::handleKeyDownEvent(SDL_Event const &event)
    {
        CharacterActor::ControlFlag flag = mapKeyToControl(event.key.keysym.sym);
        if (flag != CharacterActor::CONTROL_COUNT) {
            if (GameLogic::CharacterPtr character =
                gameLogic_->playerCharacter())
            {
                CharacterActor::ControlFlagSet flags = character->controlFlags();
                flags.set(flag, true);
                character->controlFlags(flags);
            }
        }
    }

    void GameLoop::handleKeyUpEvent(SDL_Event const &event)
    {
        CharacterActor::ControlFlag flag = mapKeyToControl(event.key.keysym.sym);
        if (flag != CharacterActor::CONTROL_COUNT) {
            if (GameLogic::CharacterPtr character =
                gameLogic_->playerCharacter())
            {
                CharacterActor::ControlFlagSet flags = character->controlFlags();
                flags.set(flag, false);
                character->controlFlags(flags);
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
