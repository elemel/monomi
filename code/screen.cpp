#include "screen.hpp"

#include <GL/gl.h>

namespace monomi {
    Screen::Screen(Window *window) :
        window_(window),
        alive_(true)
    { }
    
    Screen::~Screen()
    { }

    bool Screen::alive()
    {
        return alive_;
    }

    void Screen::update()
    { }

    void Screen::draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINES);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, 1.0f);
        glEnd();
    }

    void Screen::onOpen()
    { }

    void Screen::onSuspend()
    { }

    void Screen::onResume()
    { }

    void Screen::onClose()
    { }

    void Screen::onKeyPress(Key key, Modifiers modifiers)
    {
        alive_ = false;
    }

    void Screen::onKeyRelease(Key key, Modifiers modifiers)
    { }
}
