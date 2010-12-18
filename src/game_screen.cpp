#include "game_screen.hpp"

#include "block_actor.hpp"
#include "character_actor.hpp"
#include "debug_graphics.hpp"
#include "game.hpp"

#include <ctime>
#include <iostream>
#include <GL/gl.h>

namespace monomi {
    GameScreen::GameScreen() :
        quit_(false),
        time_(0.0f),
        dt_(1.0f / 60.0f),
        debugGraphics_(new DebugGraphics),
        game_(new Game)
    {
        camera_.scale = 7.0f;
    }

    GameScreen::~GameScreen()
    { }

    boost::shared_ptr<Screen> GameScreen::run()
    {
        time_ = 0.001f * float(SDL_GetTicks());
        do {
            pumpEvents();
            update();
            draw();
        } while (!quit_);
        return boost::shared_ptr<Screen>();
    }

    void GameScreen::pumpEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                onKeyDown(event);
                break;

            case SDL_KEYUP:
                onKeyUp(event);
                break;

            case SDL_QUIT:
                quit_ = true;
                break;
            }
        }
    }

    void GameScreen::onKeyDown(SDL_Event const &event)
    {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            quit_ = true;
            break;

        case SDLK_LEFT:
            game_->characters_.front()->controls.set(leftControl);
            break;

        case SDLK_RIGHT:
            game_->characters_.front()->controls.set(rightControl);
            break;

        case SDLK_DOWN:
            game_->characters_.front()->controls.set(downControl);
            break;

        case SDLK_UP:
            game_->characters_.front()->controls.set(upControl);
            break;

        case SDLK_SPACE:
            game_->characters_.front()->controls.set(jumpControl);
            break;
        }
    }

    void GameScreen::onKeyUp(SDL_Event const &event)
    {
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            game_->characters_.front()->controls.reset(leftControl);
            break;

        case SDLK_RIGHT:
            game_->characters_.front()->controls.reset(rightControl);
            break;

        case SDLK_DOWN:
            game_->characters_.front()->controls.reset(downControl);
            break;

        case SDLK_UP:
            game_->characters_.front()->controls.reset(upControl);
            break;

        case SDLK_SPACE:
            game_->characters_.front()->controls.reset(jumpControl);
            break;
        }
    }

    void GameScreen::update()
    {
        float time = 0.001f * float(SDL_GetTicks());
        while (time_ + dt_ <= time) {
            time_ += dt_;
            game_->update(dt_);
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
        camera_.position = game_->characters_.front()->position;
        glOrtho(camera_.position.x - camera_.scale * aspectRatio,
                camera_.position.x + camera_.scale * aspectRatio,
                camera_.position.y - camera_.scale,
                camera_.position.y + camera_.scale,
                -1.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);

        // Draw.
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
                GL_STENCIL_BUFFER_BIT);
        typedef std::vector<boost::shared_ptr<BlockActor> >::iterator BlockIterator;
        for (BlockIterator i = game_->blocks_.begin(); i != game_->blocks_.end(); ++i) {
            (*i)->debugDraw(debugGraphics_.get());
        }
        typedef std::vector<boost::shared_ptr<CharacterActor> >::iterator CharacterIterator;
        for (CharacterIterator j = game_->characters_.begin(); j != game_->characters_.end();
             ++j)
        {
            (*j)->debugDraw(debugGraphics_.get());
        }
        SDL_GL_SwapBuffers();
    }
}
