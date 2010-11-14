#ifndef MONOMI_WINDOW_HPP
#define MONOMI_WINDOW_HPP

#include <memory>
#include <boost/ptr_container/ptr_vector.hpp>

#include <boost/noncopyable.hpp>

namespace monomi {
    class Screen;

    class Window :
        private boost::noncopyable
    {
    public:
        Window();
        virtual ~Window();

        virtual Screen *topScreen();

        virtual void pushScreen(std::auto_ptr<Screen> screen);
        virtual void run();

    protected:
        boost::ptr_vector<Screen> screens_;
    };
}

#endif // MONOMI_WINDOW_HPP
