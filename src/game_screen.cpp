#include "game_screen.hpp"

#include "block.hpp"
#include "character.hpp"
#include "debug_graphics.hpp"

#include <GL/gl.h>
#include <SDL/SDL.h>

namespace monomi {
    namespace {
        std::auto_ptr<Block> createBlock(int x, int y)
        {
            std::auto_ptr<Block> block(new Block);
            block->box.p1 = Point2(float(x), float(y));
            block->box.p2 = Point2(float(x + 1), float(y + 1));
            return block;
        }
    }

    Camera::Camera() :
        scale(1.0f)
    { }

    GameScreen::GameScreen() :
        quit_(false),
        time_(0.0f),
        dt_(1.0f / 60.0f),
        debugGraphics_(new DebugGraphics),
        playerCharacter_(new Character)
    {
        camera_.scale = 5.0f;
        playerCharacter_->circle.center = Point2(1.5f, 2.5f);
        blocks_.push_back(createBlock(0, 0));
        blocks_.push_back(createBlock(1, 0));
        blocks_.push_back(createBlock(2, 0));
        blocks_.push_back(createBlock(3, 0));
        blocks_.push_back(createBlock(3, 1));
        blocks_.push_back(createBlock(3, 2));
        blocks_.push_back(createBlock(3, 3));
    }

    GameScreen::~GameScreen()
    { }

    std::auto_ptr<Screen> GameScreen::run()
    {
        time_ = 0.001f * float(SDL_GetTicks());
        do {
            pumpEvents();
            step();
            resolveCollisions();
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
            playerCharacter_->controls.left = true;
            break;

        case SDLK_RIGHT:
            playerCharacter_->controls.right = true;
            break;

        case SDLK_DOWN:
            playerCharacter_->controls.down = true;
            break;

        case SDLK_UP:
            playerCharacter_->controls.up = true;
            break;

        case SDLK_SPACE:
            playerCharacter_->controls.jump = true;
            break;
        }
    }

    void GameScreen::onKeyUp(SDL_Event const &event)
    {
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            playerCharacter_->controls.left = false;
            break;

        case SDLK_RIGHT:
            playerCharacter_->controls.right = false;
            break;

        case SDLK_DOWN:
            playerCharacter_->controls.down = false;
            break;

        case SDLK_UP:
            playerCharacter_->controls.up = false;
            break;

        case SDLK_SPACE:
            playerCharacter_->controls.jump = false;
            break;
        }
    }

    void GameScreen::step()
    {
        float time = 0.001f * float(SDL_GetTicks());
        while (time_ + dt_ <= time) {
            time_ += dt_;
            playerCharacter_->step(dt_);
        }
    }

    void GameScreen::resolveCollisions()
    {
        playerCharacter_->state = characterStates::jumping;
        for (boost::ptr_vector<Block>::iterator i = blocks_.begin();
             i != blocks_.end(); ++i)
        {
            if (intersects(playerCharacter_->circle, i->box)) {
                playerCharacter_->circle.center.y = i->box.p2.y + playerCharacter_->circle.radius;
                playerCharacter_->velocity.y = 0.0f;
                playerCharacter_->state = characterStates::standing;
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
        camera_.position = playerCharacter_->circle.center;
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
        for (boost::ptr_vector<Block>::iterator i = blocks_.begin();
             i != blocks_.end(); ++i)
        {
            i->debugDraw(debugGraphics_.get());
        }
        playerCharacter_->debugDraw(debugGraphics_.get());
        SDL_GL_SwapBuffers();
    }
}
