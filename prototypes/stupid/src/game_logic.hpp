#ifndef MONOMI_GAME_LOGIC_HPP
#define MONOMI_GAME_LOGIC_HPP

#include "character_actor.hpp"
#include "geometry.hpp"

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <Box2D/Dynamics/b2World.h>

namespace monomi {
    class DebugGraphics;

    class GameLogic : private boost::noncopyable {
    public:
        GameLogic();

        void update(float dt);
        void debugDraw(DebugGraphics *graphics);

        void createPlatform(Polygon2 const &polygon);
        void createShadow(Polygon2 const &polygon);
        void createWater(Polygon2 const &polygon);

        void createStart(Circle2 const &circle);
        void createGoal(Circle2 const &circle);

        std::vector<boost::shared_ptr<CharacterActor> > const &characters() const;

    private:
        float time_;
        boost::shared_ptr<b2World> world_;
        b2Body *worldBody_;

        std::vector<boost::shared_ptr<CharacterActor> > characters_;
    };
}

#endif // MONOMI_GAME_LOGIC_HPP
