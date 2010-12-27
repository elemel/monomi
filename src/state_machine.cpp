#include "state_machine.hpp"

#include "state.hpp"
#include "type.hpp"

#include <cassert>
#include <iostream>

namespace monomi {
    StateMachine::StateMachine(StatePtr const &state) :
        state_(state)
    {
        assert(state);
    }

    StatePtr StateMachine::state() const
    {
        return state_;
    }

    void StateMachine::state(StatePtr const &state)
    {
        assert(state);
        state_ = state;
    }

    void StateMachine::update(float dt)
    {
        if (StatePtr newState = state_->transition()) {
            state_->exit();
            state_ = newState;
            transitionSignal_();
            state_->enter();
        }
        state_->update(dt);
    }

    boost::signals2::connection
    StateMachine::connectTransitionSlot(TransitionSlot const &slot)
    {
        return transitionSignal_.connect(slot);
    }
}
