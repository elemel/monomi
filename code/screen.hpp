#ifndef MONOMI_SCREEN_HPP
#define MONOMI_SCREEN_HPP

#include "keys.hpp"

#include <boost/noncopyable.hpp>

namespace monomi {
    class Window;

    class Screen :
        private boost::noncopyable
    {
    public:
        explicit Screen(Window *window);
        virtual ~Screen();

        virtual bool alive();

        virtual void update();
        virtual void draw();

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
