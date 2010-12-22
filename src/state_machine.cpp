#include "state_machine.hpp"

#include "state.hpp"

#include <iostream>

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
                std::cout << "Changing to new state: " << typeid(*newState).name() << std::endl;
                state->enter();
            }
            state->update(dt);
        }
    }
}
