#ifndef MONOMI_SCREEN_HPP
#define MONOMI_SCREEN_HPP

#include "keys.hpp"

namespace monomi {
    class Screen {
    public:
        virtual ~Screen();

        virtual bool alive() = 0;

        virtual void update() = 0;
        virtual void draw() = 0;

        virtual void onOpen() = 0;
        virtual void onSuspend() = 0;
        virtual void onResume() = 0;
        virtual void onClose() = 0;

        virtual void onKeyPress(Key key, Modifiers modifiers) = 0;
        virtual void onKeyRelease(Key key, Modifiers modifiers) = 0;
    };
}

#endif // MONOMI_SCREEN_HPP
