#include "game_screen.hpp"

#include "game_engine.hpp"
#include "character_actor.hpp"
#include "window.hpp"

#include <GL/gl.h>

namespace monomi {
    GameScreen::GameScreen(Window *window) :
        window_(window),
        alive_(true)
    {
        gameEngine_.reset(new GameEngine(window_->width(), window_->height()));
        std::auto_ptr<CharacterActor> characterActor(new CharacterActor);
        std::auto_ptr<Actor> actor(characterActor);
        gameEngine_->addActor(actor);
    }

    bool GameScreen::alive()
    {
        return alive_;
    }

    void GameScreen::update()
    { }

    void GameScreen::draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        gameEngine_->debugDraw();
    }

    void GameScreen::onOpen()
    { }

    void GameScreen::onSuspend()
    { }

    void GameScreen::onResume()
    { }

    void GameScreen::onClose()
    { }

    void GameScreen::onKeyPress(Key key, Modifiers modifiers)
    {
        alive_ = false;
    }

    void GameScreen::onKeyRelease(Key key, Modifiers modifiers)
    { }
}
