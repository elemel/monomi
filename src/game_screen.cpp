#include "game_screen.hpp"

#include "block.hpp"
#include "character.hpp"
#include "character_factory.hpp"
#include "character_type.hpp"
#include "debug_graphics.hpp"
#include "game.hpp"
#include "random.hpp"

#include <ctime>
#include <iostream>
#include <GL/gl.h>

namespace monomi {
    namespace {
        boost::shared_ptr<Block> createBlock(int x, int y)
        {
            boost::shared_ptr<Block> block(new Block);
            block->box.p1 = Point2(float(x), float(y));
            block->box.p2 = Point2(float(x + 1), float(y + 1));
            return block;
        }
    }

    GameScreen::GameScreen() :
        quit_(false),
        time_(0.0f),
        dt_(1.0f / 60.0f),
        random_(new Random(std::time(0))),
        debugGraphics_(new DebugGraphics),
        characterFactory_(new CharacterFactory),
        game_(new Game)
    {
        camera_.scale = 7.0f;

        // Create characters.
        characters_.push_back(characterFactory_->createEarthMaster());
        characters_.back()->position = Point2(2.0f, 2.0f);
        characters_.push_back(characterFactory_->createSamurai());
        characters_.back()->position = Point2(7.0f, 5.0f);
        characters_.push_back(characterFactory_->createSamurai());
        characters_.back()->position = Point2(9.0f, 5.0f);
        characters_.push_back(characterFactory_->createSamurai());
        characters_.back()->position = Point2(11.0f, 5.0f);

        // Create blocks.
        blocks_.push_back(createBlock(0, 0));
        blocks_.push_back(createBlock(0, 3));
        blocks_.push_back(createBlock(1, 0));
        blocks_.push_back(createBlock(2, 0));
        blocks_.push_back(createBlock(3, 0));
        blocks_.push_back(createBlock(3, 1));
        blocks_.push_back(createBlock(3, 2));
        blocks_.push_back(createBlock(3, 3));
        blocks_.push_back(createBlock(3, 4));
        blocks_.push_back(createBlock(3, 5));
        blocks_.push_back(createBlock(3, 6));
        blocks_.push_back(createBlock(4, 0));
        blocks_.push_back(createBlock(5, 0));
        blocks_.push_back(createBlock(6, 0));
        blocks_.push_back(createBlock(7, 0));
        blocks_.push_back(createBlock(7, 3));
        blocks_.push_back(createBlock(7, 4));
        blocks_.push_back(createBlock(7, 5));
        blocks_.push_back(createBlock(7, 6));
        blocks_.push_back(createBlock(7, 7));
        blocks_.push_back(createBlock(7, 8));
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

    boost::shared_ptr<Screen> GameScreen::run()
    {
        time_ = 0.001f * float(SDL_GetTicks());
        do {
            pumpEvents();
            step();
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
            characters_.front()->controls.set(leftControl);
            break;

        case SDLK_RIGHT:
            characters_.front()->controls.set(rightControl);
            break;

        case SDLK_DOWN:
            characters_.front()->controls.set(downControl);
            break;

        case SDLK_UP:
            characters_.front()->controls.set(upControl);
            break;

        case SDLK_SPACE:
            characters_.front()->controls.set(jumpControl);
            break;
        }
    }

    void GameScreen::onKeyUp(SDL_Event const &event)
    {
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            characters_.front()->controls.reset(leftControl);
            break;

        case SDLK_RIGHT:
            characters_.front()->controls.reset(rightControl);
            break;

        case SDLK_DOWN:
            characters_.front()->controls.reset(downControl);
            break;

        case SDLK_UP:
            characters_.front()->controls.reset(upControl);
            break;

        case SDLK_SPACE:
            characters_.front()->controls.reset(jumpControl);
            break;
        }
    }

    void GameScreen::step()
    {
        float time = 0.001f * float(SDL_GetTicks());
        while (time_ + dt_ <= time) {
            time_ += dt_;
            performAI();
            typedef std::vector<boost::shared_ptr<Character> >::iterator Iterator;
            for (Iterator i = characters_.begin(); i != characters_.end(); ++i)
            {
                (*i)->step(dt_);
            }
            resolveCollisions();
        }
    }

    void GameScreen::performAI()
    {
        typedef std::vector<boost::shared_ptr<Character> >::iterator Iterator;
        for (Iterator i = characters_.begin() + 1; i != characters_.end(); ++i)
        {
            if (random_->generate() <= dt_) {
                int face = int(random_->generate() * 3.0f) - 1;
                (*i)->controls.set(leftControl, (face == -1));
                (*i)->controls.set(rightControl, (face == 1));
            }
            if (random_->generate() <= dt_) {
                (*i)->controls.set(jumpControl, (random_->generate() <= 0.5f));
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
        typedef std::vector<boost::shared_ptr<Character> >::iterator CharacterIterator;
        for (CharacterIterator i = characters_.begin(); i != characters_.end();
             ++i)
        {
            if ((*i)->alive) {
                // Resolve collisions. Make multiple iterations, resolving only
                // the deepest collision found during each iteration.
                for (int j = 0; j < 3; ++j) {
                    // Find the deepest collision.
                    float maxSquaredLength = -1.0f;
                    LineSegment2 maxSeparator;
                    typedef std::vector<boost::shared_ptr<Block> >::iterator BlockIterator;
                    for (BlockIterator k = blocks_.begin(); k != blocks_.end();
                         ++k)
                    {
                        if (intersects((*i)->bottomCircle(), (*k)->box)) {
                            LineSegment2 separator =
                                separate((*i)->bottomCircle(), (*k)->box);
                            if (separator.squaredLength() >= maxSquaredLength)
                            {
                                maxSquaredLength = separator.squaredLength();
                                maxSeparator = separator;
                            }
                        }
                        if (intersects((*i)->topCircle(), (*k)->box)) {
                            LineSegment2 separator =
                                separate((*i)->topCircle(), (*k)->box);
                            if (separator.squaredLength() >= maxSquaredLength)
                            {
                                maxSquaredLength = separator.squaredLength();
                                maxSeparator = separator;
                            }
                        }
                    }

                    // Resolve the deepest collision.
                    if (maxSquaredLength >= 0.0f) {
                        // Separate the colliding shapes, and cancel any
                        // negative velocity along the collision normal.
                        Vector2 normal = maxSeparator.p2 - maxSeparator.p1;
                        (*i)->position += normal;
                        normal.normalize();
                        (*i)->velocity -= (normal *
                                           std::min(dot((*i)->velocity, normal),
                                                    0.0f));
                    }
                }
            }
            updateTouchFlags(i->get());
        }
    }

    void GameScreen::updateTouchFlags(Character *character)
    {
        // Clear touch flags.
        character->touchLeft = false;
        character->touchRight = false;
        character->touchDown = false;
        character->touchUp = false;

        // Set touch flags.
        for (int i = 0; i < 2; ++i) {
            Circle circle = i ? character->bottomCircle() :
                                character->topCircle();
            circle.radius += 0.02f;
            typedef std::vector<boost::shared_ptr<Block> >::iterator Iterator;
            for (Iterator j = blocks_.begin(); j != blocks_.end(); ++j) {
                if (intersects(circle, (*j)->box)) {
                    LineSegment2 separator = separate(circle, (*j)->box);
                    Vector2 normal = separator.p2 - separator.p1;
                    normal.normalize();
                    float velocity = dot(character->velocity, normal);
                    if (std::abs(velocity) <= 0.02f) {
                        if (normal.x >= 0.98f) {
                            character->touchLeft = true;
                        }
                        if (normal.x <= -0.98f) {
                            character->touchRight = true;
                        }
                        if (normal.y >= 0.98f) {
                            character->touchDown = true;
                        }
                        if (normal.y <= -0.98f) {
                            character->touchUp = true;
                        }
                    }
                }
            }
        }
    }

    void GameScreen::resolveCharacterCollisions()
    {
        boost::shared_ptr<Character> playerCharacter = characters_.front();
        typedef std::vector<boost::shared_ptr<Character> >::iterator Iterator;
        for (Iterator i = characters_.begin() + 1; i != characters_.end(); ++i)
        {
            if (playerCharacter->alive && (*i)->alive &&
                (intersects(playerCharacter->bottomCircle(),
                            (*i)->bottomCircle()) ||
                 intersects(playerCharacter->bottomCircle(),
                            (*i)->topCircle()) ||
                 intersects(playerCharacter->topCircle(),
                            (*i)->bottomCircle()) ||
                 intersects(playerCharacter->topCircle(),
                            (*i)->topCircle())))
            {
                int side = int(sign((*i)->position.x -
                                    playerCharacter->position.x));
                if (side == (*i)->face) {
                    (*i)->alive = false;
                } else {
                    playerCharacter->alive = false;
                }
                playerCharacter->velocity *= 0.5f;
                (*i)->velocity *= 0.5f;
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
        camera_.position = characters_.front()->position;
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
        typedef std::vector<boost::shared_ptr<Block> >::iterator BlockIterator;
        for (BlockIterator i = blocks_.begin(); i != blocks_.end(); ++i) {
            (*i)->debugDraw(debugGraphics_.get());
        }
        typedef std::vector<boost::shared_ptr<Character> >::iterator CharacterIterator;
        for (CharacterIterator j = characters_.begin(); j != characters_.end();
             ++j)
        {
            (*j)->debugDraw(debugGraphics_.get());
        }
        SDL_GL_SwapBuffers();
    }
}
