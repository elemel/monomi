#include "screen.hpp"

#include <GL/gl.h>

namespace monomi {
    Screen::Screen(Window *window) :
        window_(window),
        alive_(true)
    { }
    
    Screen::~Screen()
    { }

    bool Screen::alive() const
    {
        return alive_;
    }

    void Screen::open()
    { }

    void Screen::suspend()
    { }

    void Screen::resume()
    { }

    void Screen::close()
    { }

    void Screen::update()
    { }

    void Screen::draw() const
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINES);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, 1.0f);
        glEnd();
    }
}
