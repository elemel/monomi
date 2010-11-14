#include "window.hpp"

#include "screen.hpp"

namespace monomi {
    Window::Window()
    { }
    
    Window::~Window()
    { }

    Screen *Window::topScreen()
    {
        return screens_.empty() ? 0 : &screens_.back();
    }

    void Window::pushScreen(std::auto_ptr<Screen> screen)
    {
        screens_.push_back(screen.release());
    }

    void Window::run()
    { }
}
