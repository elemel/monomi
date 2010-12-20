#include "component_registry.hpp"

#include "component.hpp"

#include <iostream>

namespace monomi {
    void ComponentRegistry::add(boost::shared_ptr<Component> const &component)
    {
        if (component) {
            components_.push_back(component);
        }
    }

    void ComponentRegistry::update(float dt)
    {
        typedef std::vector<boost::weak_ptr<Component> >::iterator Iterator;
        Iterator i = components_.begin();
        for (Iterator j = components_.begin(); j != components_.end(); ++j) {
            if (boost::shared_ptr<Component> component = j->lock()) {
                component->update(dt);
                *i++ = *j;
            }
        }
        components_.erase(i, components_.end());
    }
}
