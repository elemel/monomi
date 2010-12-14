#ifndef MONOMI_OBJECT_REGISTRY_HPP
#define MONOMI_OBJECT_REGISTRY_HPP

#include <map>
#include <string>
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/thread/mutex.hpp>

namespace monomi {
    class ObjectRegistry;

    typedef boost::shared_ptr<ObjectRegistry> ObjectRegistryPtr;
    typedef boost::weak_ptr<ObjectRegistry> ObjectRegistryWeakPtr;

    class ObjectRegistry {
    public:
        template <typename T>
        boost::shared_ptr<T> get(std::string const &name);

        template <typename T>
        void set(std::string const &name, boost::shared_ptr<T> const &object);

    private:
        typedef std::map<std::string, boost::any> ObjectMap;
        typedef ObjectMap::const_iterator ObjectConstIterator;

        boost::mutex mutex_;
        ObjectMap objects_;
    };

    template <typename T>
    boost::shared_ptr<T> ObjectRegistry::get(std::string const &name)
    {
        boost::lock_guard<boost::mutex> guard(mutex_);
        ObjectConstIterator i = objects_.find(name);
        if (i == objects_.end()) {
            return boost::shared_ptr<T>();
        } else {
            return boost::any_cast<boost::weak_ptr<T> >(i->second).lock();
        }
    }

    template <typename T>
    void ObjectRegistry::set(std::string const &name,
                             boost::shared_ptr<T> const &object)
    {
        boost::lock_guard<boost::mutex> guard(mutex_);
        if (object) {
            boost::any wrapper = boost::weak_ptr<T>(object);
            std::pair<std::string, boost::any> entry(name, wrapper);
            objects_.insert(entry);
        } else {
            objects_.erase(name);
        }
    }
}

#endif // MONOMI_OBJECT_REGISTRY_HPP
