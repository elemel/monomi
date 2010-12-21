#ifndef MONOMI_STATE_HPP
#define MONOMI_STATE_HPP

#include <boost/shared_ptr.hpp>

namespace monomi {
    class State {
    public:
        virtual ~State()
        { }

        virtual void enter() = 0;
        virtual boost::shared_ptr<State> transition() = 0;
        virtual void update(float dt) = 0;
        virtual void exit() = 0;
    };
}

#endif // MONOMI_STATE_HPP
