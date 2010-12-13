#ifndef MONOMI_EVENT_SUBSCRIBER_HPP
#define MONOMI_EVENT_SUBSCRIBER_HPP

#include "event.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace monomi {
    class EventSubscriber;

    typedef boost::shared_ptr<EventSubscriber> EventSubscriberPtr;
    typedef boost::weak_ptr<EventSubscriber> EventSubscriberWeakPtr;

    class EventSubscriber {
    public:
        virtual ~EventSubscriber()
        { }

        virtual void receive(Event const &event) = 0;
    };
}

#endif // MONOMI_EVENT_SUBSCRIBER_HPP
