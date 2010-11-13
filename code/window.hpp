#ifndef MONOMI_WINDOW_HPP
#define MONOMI_WINDOW_HPP

#include <memory>
#include <boost/ptr_container/ptr_vector.hpp>

namespace monomi {
    class Screen;

    class Window {
    public:
        Window();
        virtual ~Window();

        virtual Screen *topScreen();
        virtual const Screen *topScreen() const;

        virtual void pushScreen(std::auto_ptr<Screen> screen);
        virtual void run();

    protected:
        boost::ptr_vector<Screen> screens_;
    };
}

#endif // MONOMI_WINDOW_HPP
