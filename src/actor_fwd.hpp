#ifndef MONOMI_ACTOR_FWD_HPP
#define MONOMI_ACTOR_FWD_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace monomi {
    class Actor;

    typedef boost::shared_ptr<Actor> ActorPtr;
    typedef boost::weak_ptr<Actor> ActorWeakPtr;
    typedef boost::shared_ptr<Actor const> ActorConstPtr;
    typedef boost::weak_ptr<Actor const> ActorConstWeakPtr;
}

#endif // MONOMI_ACTOR_FWD_HPP
