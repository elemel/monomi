#ifndef MONOMI_SCREEN_HPP
#define MONOMI_SCREEN_HPP

#include <boost/shared_ptr.hpp>

namespace monomi {
    class Screen {
    public:
        virtual ~Screen();

        virtual boost::shared_ptr<Screen> run() = 0;
    };
}

#endif // MONOMI_SCREEN_HPP
