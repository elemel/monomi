#ifndef MONOMI_SCREEN_HPP
#define MONOMI_SCREEN_HPP

#include <memory>

namespace monomi {
    class Screen {
    public:
        virtual ~Screen()
        { }

        virtual std::auto_ptr<Screen> run() = 0;
    };
}

#endif // MONOMI_SCREEN_HPP
