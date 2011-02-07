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
        typedef boost::shared_ptr<CharacterActor> CharacterPtr;
        typedef std::vector<CharacterPtr> CharacterVector;
        typedef std::vector<b2Fixture *> FixtureVector;

        GameLogic();

        CharacterPtr playerCharacter() const;
        CharacterVector const &characters() const;

        void update(float dt);
        void debugDraw(DebugGraphics *graphics);

        void createPlatform(Polygon2 const &polygon);
        void createShadow(Polygon2 const &polygon);
        void createWater(Polygon2 const &polygon);

        void createStart(Circle2 const &circle);
        void createGoal(Circle2 const &circle);

    private:
        float time_;
        boost::shared_ptr<b2World> world_;
        b2Body *worldBody_;

        CharacterVector characters_;
        CharacterPtr playerCharacter_;

        FixtureVector startFixtures_;
        FixtureVector goalFixtures_;
    };
}

#endif // MONOMI_GAME_LOGIC_HPP
