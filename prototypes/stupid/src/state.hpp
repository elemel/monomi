#ifndef MONOMI_STATE_HPP
#define MONOMI_STATE_HPP

#include "state_fwd.hpp"

#include <iostream>

namespace monomi {
    class State {
    public:
        virtual ~State()
        { }

        virtual void enter() = 0;
        virtual void leave() = 0;

        virtual StatePtr transition() = 0;
        virtual void update(float dt) = 0;

        virtual void print(std::ostream &out) const = 0;
    };

    inline std::ostream &operator<<(std::ostream &out, State const &state)
    {
        state.print(out);
        return out;
    }
}

#endif // MONOMI_STATE_HPP
