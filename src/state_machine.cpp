#include "state_machine.hpp"

#include "state.hpp"

namespace monomi {
    StateMachine::StateMachine()
    { }

    StateMachine::StateMachine(boost::shared_ptr<State> const &state) :
        state(state)
    { }

    void StateMachine::update(float dt)
    {
        if (state) {
            if (boost::shared_ptr<State> newState = state->transition()) {
                state->exit();
                state = newState;
                state->enter();
            }
            state->update(dt);
        }
    }
}
