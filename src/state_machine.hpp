#ifndef MONOMI_STATE_MACHINE_HPP
#define MONOMI_STATE_MACHINE_HPP

#include "state.hpp"

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

namespace monomi {
    class State;

    class StateMachine :
        private boost::noncopyable
    {
    public:
        typedef boost::signal<void ()> TransitionSignal;
        typedef TransitionSignal::slot_type TransitionSlot;

        explicit StateMachine(boost::shared_ptr<State> const &state);

        boost::shared_ptr<State> state();
        boost::shared_ptr<State const> state() const;
        void state(boost::shared_ptr<State> const &state);

        void update(float dt);

        boost::signals::connection
        connectTransitionSlot(TransitionSlot const &slot);

    private:
        boost::shared_ptr<State> state_;
        TransitionSignal transitionSignal_;
    };
}

#endif // MONOMI_STATE_MACHINE_HPP
