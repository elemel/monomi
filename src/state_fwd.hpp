#ifndef MONOMI_STATE_FWD_HPP
#define MONOMI_STATE_FWD_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace monomi {
    class State;

    typedef boost::shared_ptr<State> StatePtr;
    typedef boost::weak_ptr<State> StateWeakPtr;
    typedef boost::shared_ptr<State const> StateConstPtr;
    typedef boost::weak_ptr<State const> StateConstWeakPtr;
}

#endif // MONOMI_STATE_FWD_HPP
