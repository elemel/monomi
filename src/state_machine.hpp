#ifndef MONOMI_STATE_MACHINE_HPP
#define MONOMI_STATE_MACHINE_HPP

#include "state_fwd.hpp"

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

namespace monomi {
    // State machine that always has a single current state.
    //
    // See: State
    class StateMachine :
        private boost::noncopyable
    {
    public:
        typedef boost::signals2::signal<void ()> TransitionSignal;
        typedef TransitionSignal::slot_type TransitionSlot;

        // Construct a state machine with the specified state, which must not
        // be null.
        explicit StateMachine(StatePtr const &state);

        // Return the current state.
        StatePtr state() const;

        // Set the state. The specified state must not be null.
        void state(StatePtr const &state);

        // Update the state machine. During the update, the current state may
        // transition to another. Also updates the current state.
        void update(float dt);

        // Connect a transition slot. The slot will be invoked during each
        // state transition.
        boost::signals2::connection
        connectTransitionSlot(TransitionSlot const &slot);

    private:
        StatePtr state_;
        TransitionSignal transitionSignal_;
    };
}

#endif // MONOMI_STATE_MACHINE_HPP
