#include "game_screen.hpp"

#include "block_actor.hpp"
#include "character_actor.hpp"
#include "debug_graphics.hpp"
#include "game.hpp"
#include "random.hpp"

#include <ctime>
#include <iostream>
#include <SDL_opengl.h>

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
        boost::shared_ptr<CharacterActor> actor =
            boost::dynamic_pointer_cast<CharacterActor>(game_->actors_.front());
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            quit_ = true;
            break;

        case SDLK_LEFT:
            actor->inputs.set(leftInput);
            break;

        case SDLK_RIGHT:
            actor->inputs.set(rightInput);
            break;

        case SDLK_DOWN:
            actor->inputs.set(downInput);
            break;

        case SDLK_UP:
            actor->inputs.set(upInput);
            break;

        case SDLK_SPACE:
            actor->inputs.set(jumpInput);
            break;
        }
    }

    void GameScreen::onKeyUp(SDL_Event const &event)
    {
        boost::shared_ptr<CharacterActor> actor =
            boost::dynamic_pointer_cast<CharacterActor>(game_->actors_.front());
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            actor->inputs.reset(leftInput);
            break;

        case SDLK_RIGHT:
            actor->inputs.reset(rightInput);
            break;

        case SDLK_DOWN:
            actor->inputs.reset(downInput);
            break;

        case SDLK_UP:
            actor->inputs.reset(upInput);
            break;

        case SDLK_SPACE:
            actor->inputs.reset(jumpInput);
            break;
        }
    }

    void GameScreen::update()
    {
        float time = 0.001f * float(SDL_GetTicks());
        while (time_ + dt_ <= time) {
            time_ += dt_;
            performAI(dt_);
            game_->update(dt_);
        }
    }

    void GameScreen::performAI(float dt)
    {
        if (!game_->actors_.empty()) {
            typedef std::vector<boost::shared_ptr<Actor> >::iterator Iterator;
            for (Iterator i = game_->actors_.begin() + 1;
                 i != game_->actors_.end(); ++i)
            {
                if (boost::shared_ptr<CharacterActor> actor = boost::dynamic_pointer_cast<CharacterActor>(*i)) {
                    if (game_->random_->generate() <= dt) {
                        int face = int(game_->random_->generate() * 3.0f) - 1;
                        actor->inputs.set(leftInput, (face == -1));
                        actor->inputs.set(rightInput, (face == 1));
                    }
                    if (game_->random_->generate() <= dt) {
                        actor->inputs.set(jumpInput,
                                          (game_->random_->generate() <= 0.5f));
                    }
                }
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
        if (!game_->actors_.empty()) {
            camera_.position = boost::dynamic_pointer_cast<CharacterActor>(game_->actors_.front())->position;
        }
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
        typedef std::vector<boost::shared_ptr<Actor> >::iterator ActorIterator;
        for (ActorIterator i = game_->actors_.begin();
             i != game_->actors_.end(); ++i)
        {
            (*i)->debugDraw(debugGraphics_.get());
        }
        SDL_GL_SwapBuffers();
    }
}
