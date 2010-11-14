#include "game_screen.hpp"

#include <GL/gl.h>

namespace monomi {
    GameScreen::GameScreen(Window *window) :
        window_(window),
        alive_(true)
    { }

    bool GameScreen::alive()
    {
        return alive_;
    }

    void GameScreen::update()
    { }

    void GameScreen::draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINES);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, 1.0f);
        glEnd();
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
