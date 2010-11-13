#ifndef MONOMI_SCREEN_HPP
#define MONOMI_SCREEN_HPP

#include "keys.hpp"

namespace monomi {
    class Window;

    class Screen {
    public:
        explicit Screen(Window *window);
        virtual ~Screen();

        bool alive() const;

        virtual void update();
        virtual void draw() const;

        virtual void onOpen();
        virtual void onSuspend();
        virtual void onResume();
        virtual void onClose();

        virtual void onKeyPress(Key key, Modifiers modifiers);
        virtual void onKeyRelease(Key key, Modifiers modifiers);

    protected:
        Window *window_;
        bool alive_;
    };
}

#endif // MONOMI_SCREEN_HPP
