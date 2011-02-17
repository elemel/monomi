#ifndef MONOMI_ACTOR_HPP
#define MONOMI_ACTOR_HPP

#include <iostream>

namespace monomi {
    class GameLogic;
    class Vector2;

    class Actor {
    public:
        virtual ~Actor()
        { }

        virtual void create(GameLogic *logic, Vector2 const &position) = 0;
        virtual void destroy() = 0;

        virtual void update(float dt) = 0;
        virtual void print(std::ostream &out) const = 0;
    };

    inline std::ostream &operator<<(std::ostream &out, Actor const &actor)
    {
        actor.print(out);
        return out;
    }
}

#endif // MONOMI_ACTOR_HPP
