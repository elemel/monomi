#ifndef MONOMI_COMPONENT_REGISTRY_HPP
#define MONOMI_COMPONENT_REGISTRY_HPP

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace monomi {
    class Component;

    class ComponentRegistry {
    public:
        void add(boost::shared_ptr<Component> const &component);
        void update(float dt);

    private:
        std::vector<boost::weak_ptr<Component> > components_;
    };
}

#endif // MONOMI_COMPONENT_REGISTRY_HPP
