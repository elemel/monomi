#include "game_screen.hpp"

#include "block.hpp"
#include "character.hpp"
#include "debug_graphics.hpp"
#include "random.hpp"

#include <ctime>
#include <iostream>
#include <GL/gl.h>

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
        random_(new Random(std::time(0))),
        debugGraphics_(new DebugGraphics)
    {
        camera_.scale = 7.0f;

        // Create characters.
        characters_.push_back(new Character);
        characters_.back().circle.center = Point2(2.0f, 2.0f);
        characters_.push_back(new Character);
        characters_.back().circle.center = Point2(7.0f, 5.0f);
        characters_.push_back(new Character);
        characters_.back().circle.center = Point2(9.0f, 5.0f);
        characters_.push_back(new Character);
        characters_.back().circle.center = Point2(11.0f, 5.0f);

        // Create blocks.
        blocks_.push_back(createBlock(0, 0));
        blocks_.push_back(createBlock(1, 0));
        blocks_.push_back(createBlock(2, 0));
        blocks_.push_back(createBlock(3, 0));
        blocks_.push_back(createBlock(3, 1));
        blocks_.push_back(createBlock(3, 2));
        blocks_.push_back(createBlock(3, 3));
        blocks_.push_back(createBlock(0, 3));
        blocks_.push_back(createBlock(4, 0));
        blocks_.push_back(createBlock(5, 0));
        blocks_.push_back(createBlock(6, 0));
        blocks_.push_back(createBlock(7, 0));
        blocks_.push_back(createBlock(8, 0));
        blocks_.push_back(createBlock(9, 0));
        blocks_.push_back(createBlock(10, 0));
        blocks_.push_back(createBlock(11, 0));
        blocks_.push_back(createBlock(12, 0));
        blocks_.push_back(createBlock(13, 0));
        blocks_.push_back(createBlock(14, 0));
        blocks_.push_back(createBlock(15, 0));
        blocks_.push_back(createBlock(16, 0));
        blocks_.push_back(createBlock(17, 0));
        blocks_.push_back(createBlock(18, 0));
    }

    GameScreen::~GameScreen()
    { }

    std::auto_ptr<Screen> GameScreen::run()
    {
        time_ = 0.001f * float(SDL_GetTicks());
        do {
            pumpEvents();
            step();
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
            characters_.front().controls.left = true;
            break;

        case SDLK_RIGHT:
            characters_.front().controls.right = true;
            break;

        case SDLK_DOWN:
            characters_.front().controls.down = true;
            break;

        case SDLK_UP:
            characters_.front().controls.up = true;
            break;

        case SDLK_SPACE:
            characters_.front().controls.jump = true;
            break;
        }
    }

    void GameScreen::onKeyUp(SDL_Event const &event)
    {
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            characters_.front().controls.left = false;
            break;

        case SDLK_RIGHT:
            characters_.front().controls.right = false;
            break;

        case SDLK_DOWN:
            characters_.front().controls.down = false;
            break;

        case SDLK_UP:
            characters_.front().controls.up = false;
            break;

        case SDLK_SPACE:
            characters_.front().controls.jump = false;
            break;
        }
    }

    void GameScreen::step()
    {
        float time = 0.001f * float(SDL_GetTicks());
        while (time_ + dt_ <= time) {
            time_ += dt_;
            performAI();
            for (boost::ptr_vector<Character>::iterator i = characters_.begin();
                 i != characters_.end(); ++i)
            {
                i->step(dt_);
            }
            resolveCollisions();
        }
    }

    void GameScreen::performAI()
    {
        for (boost::ptr_vector<Character>::iterator i = characters_.begin() + 1;
             i != characters_.end(); ++i)
        {
            if (random_->generate() <= dt_) {
                int face = int(random_->generate() * 3.0f) - 1;
                i->controls.left = (face == -1);
                i->controls.right = (face == 1);
            }
            if (random_->generate() <= dt_) {
                i->controls.jump = (random_->generate() <= 0.5f);
            }
        }
    }

    void GameScreen::resolveCollisions()
    {
        resolveBlockCollisions();
        resolveCharacterCollisions();
    }

    void GameScreen::resolveBlockCollisions()
    {
        for (boost::ptr_vector<Character>::iterator i = characters_.begin();
             i != characters_.end(); ++i)
        {
            // Mark the character as falling until proven otherwise.
            //
            // TODO: Something more robust that also works for wall sliding.
            i->state = characterStates::jumping;

            if (!i->alive) {
                continue;
            }

            // Make multiple iterations, resolving only the deepest collision
            // found during each iteration.
            for (int j = 0; j < 3; ++j) {
                // Find the deepest collision.
                float maxSquaredLength = -1.0f;
                LineSegment2 maxSeparator;
                for (boost::ptr_vector<Block>::iterator k = blocks_.begin();
                     k != blocks_.end(); ++k)
                {
                    if (intersects(i->circle, k->box)) {
                        LineSegment2 separator =
                            separate(i->circle, k->box);
                        if (separator.squaredLength() >= maxSquaredLength) {
                            maxSquaredLength = separator.squaredLength();
                            maxSeparator = separator;
                        }
                    }
                }

                // Resolve the deepest collision.
                if (maxSquaredLength >= 0.0f) {
                    // Separate the colliding shapes, and cancel any negative
                    // velocity along the collision normal.
                    Vector2 normal = maxSeparator.p2 - maxSeparator.p1;
                    i->circle.center += normal;
                    normal.normalize();
                    i->velocity -= normal * std::min(dot(i->velocity, normal),
                                                     0.0f);

                    // Mark the character as standing if it collided with the
                    // ground.
                    if (normal.y >= 0.9f) {
                        i->state = characterStates::walking;
                    }
                }
            }
        }
    }

    void GameScreen::resolveCharacterCollisions()
    {
        Character *playerCharacter = &characters_.front();
        typedef boost::ptr_vector<Character>::iterator Iterator;
        for (Iterator i = characters_.begin() + 1; i != characters_.end(); ++i)
        {
            if (playerCharacter->alive && i->alive && intersects(playerCharacter->circle, i->circle)) {
                int side = int(sign(i->circle.center.x - playerCharacter->circle.center.x));
                if (side == i->face) {
                    i->alive = false;
                } else {
                    playerCharacter->alive = false;
                }
                playerCharacter->velocity *= 0.5f;
                i->velocity *= 0.5f;
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
        camera_.position = characters_.front().circle.center;
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
        for (boost::ptr_vector<Character>::iterator j = characters_.begin();
             j != characters_.end(); ++j)
        {
            j->debugDraw(debugGraphics_.get());
        }
        SDL_GL_SwapBuffers();
    }
}
