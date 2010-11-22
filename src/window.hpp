#ifndef MONOMI_WINDOW_HPP
#define MONOMI_WINDOW_HPP

#include <memory>

namespace monomi {
    class Screen;

    class Window {
    public:
        virtual ~Window();

        virtual int width() = 0;
        virtual int height() = 0;
        virtual Screen *topScreen() = 0;

        virtual void pushScreen(std::auto_ptr<Screen> screen) = 0;
        virtual void run() = 0;
    };
}

#endif // MONOMI_WINDOW_HPP
