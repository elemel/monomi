#ifndef MONOMI_COMPONENT_HPP
#define MONOMI_COMPONENT_HPP

namespace monomi {
    class Component {
    public:
        virtual ~Component()
        { }

        virtual void update(float dt) = 0;
    };
}

#endif // MONOMI_COMPONENT_HPP
