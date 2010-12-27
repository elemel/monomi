#include "state_machine.hpp"

#include "state.hpp"
#include "type.hpp"

#include <cassert>
#include <iostream>

namespace monomi {
    StateMachine::StateMachine(boost::shared_ptr<State> const &state) :
        state_(state)
    {
        assert(state);
    }

    boost::shared_ptr<State> StateMachine::state()
    {
        return state_;
    }

    boost::shared_ptr<State const> StateMachine::state() const
    {
        return state_;
    }

    void StateMachine::state(boost::shared_ptr<State> const &state)
    {
        assert(state);
        state_ = state;
    }

    void StateMachine::update(float dt)
    {
        if (boost::shared_ptr<State> newState = state_->transition()) {
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
