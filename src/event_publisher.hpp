#ifndef MONOMI_EVENT_PUBLISHER_HPP
#define MONOMI_EVENT_PUBLISHER_HPP

#include "event.hpp"
#include "event_subscriber.hpp"

#include <vector>

namespace monomi {
    class EventPublisher {
    public:
        void subscribe(EventSubscriberPtr const &subscriber);
        void unsubscribe(EventSubscriberPtr const &subscriber);

        void publish(Event const &event);
        void gc();

    private:
        typedef std::vector<EventSubscriberWeakPtr> SubscriberVector;
        typedef SubscriberVector::iterator SubscriberIterator;

        SubscriberVector subscribers_;
    };
}

#endif // MONOMI_EVENT_PUBLISHER_HPP
