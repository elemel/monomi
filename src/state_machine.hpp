#ifndef MONOMI_STATE_MACHINE_HPP
#define MONOMI_STATE_MACHINE_HPP

#include "state.hpp"

#include <boost/shared_ptr.hpp>

namespace monomi {
    class State;

    class StateMachine {
    public:
        StateMachine();
        explicit StateMachine(boost::shared_ptr<State> const &state);

        void update(float dt);

        boost::shared_ptr<State> state;
    };
}

#endif // MONOMI_STATE_MACHINE_HPP
