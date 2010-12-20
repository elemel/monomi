#include "component_registry.hpp"

#include "component.hpp"

namespace monomi {
    void ComponentRegistry::add(boost::shared_ptr<Component> const &component)
    {
        components_.push_back(component);
    }

    void ComponentRegistry::update(float dt)
    {
        typedef std::vector<boost::weak_ptr<Component> >::iterator Iterator;
        for (Iterator i = components_.begin(); i != components_.end(); ++i) {
            if (boost::shared_ptr<Component> component = i->lock()) {
                component->update(dt);
            }
        }
    }
}
