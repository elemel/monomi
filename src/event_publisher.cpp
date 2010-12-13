#include "event_publisher.hpp"

namespace monomi {
    namespace {
        template <typename T>
        class WeakPtrEquivalent {
        private:
            boost::weak_ptr<T> p1_;

        public:
            explicit WeakPtrEquivalent(boost::weak_ptr<T> const &p1) :
                p1_(p1)
            { }

            bool operator()(boost::weak_ptr<T> const &p2)
            {
                return !(p1_ < p2) && !(p2 < p1_);
            }
        };

        template <typename T>
        class WeakPtrExpired {
        public:
            bool operator()(boost::weak_ptr<T> const &p)
            {
                return p.lock() == 0;
            }
        };
    }

    void EventPublisher::subscribe(EventSubscriberPtr const &subscriber)
    {
        WeakPtrEquivalent<EventSubscriber> predicate(subscriber);
        SubscriberIterator i = std::find_if(subscribers_.begin(),
                                            subscribers_.end(), predicate);
        if (i == subscribers_.end()) {
            subscribers_.push_back(subscriber);
        }
    }

    void EventPublisher::unsubscribe(EventSubscriberPtr const &subscriber)
    {
        WeakPtrEquivalent<EventSubscriber> predicate(subscriber);
        SubscriberIterator i = std::find_if(subscribers_.begin(),
                                            subscribers_.end(), predicate);
        if (i != subscribers_.end()) {
            *i = EventSubscriberWeakPtr();
        }
    }

    void EventPublisher::publish(Event const &event)
    {
        for (SubscriberVector::size_type i = 0; i < subscribers_.size(); ++i) {
            if (EventSubscriberPtr subscriber = subscribers_[i].lock()) {
                subscriber->receive(event);
            } else {
                subscribers_[i] = EventSubscriberWeakPtr();
            }
        }
    }

    void EventPublisher::gc()
    {
        WeakPtrExpired<EventSubscriber> predicate;
        subscribers_.erase(std::remove_if(subscribers_.begin(),
                                          subscribers_.end(), predicate),
                           subscribers_.end());
    }
}
