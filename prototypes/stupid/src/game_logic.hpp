#ifndef MONOMI_GAME_LOGIC_HPP
#define MONOMI_GAME_LOGIC_HPP

#include "category_flag.hpp"
#include "geometry.hpp"

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <Box2D/Dynamics/b2World.h>

namespace monomi {
    class CharacterActor;
    class DebugGraphics;

    class GameLogic : private boost::noncopyable {
    public:
        typedef boost::shared_ptr<CharacterActor> CharacterPtr;
        typedef std::vector<CharacterPtr> CharacterVector;
        typedef std::vector<b2Fixture *> FixtureVector;

        GameLogic();

        float time() const;

        b2World *world() const;
        b2Body *worldBody() const;

        CharacterPtr playerCharacter() const;
        CharacterVector const &characters() const;

        void update(float dt);
        void debugDraw(DebugGraphics *graphics);

        void createPlatform(Polygon2 const &polygon);
        void createShadow(Polygon2 const &polygon);
        void createWater(Polygon2 const &polygon);

        void createStart(Circle2 const &circle);
        void createGoal(Circle2 const &circle);

        CharacterPtr createCharacter(CategoryFlag category,
                                     Vector2 const &position);
        void destroyCharacter(CharacterPtr character);

    private:
        float time_;
        boost::shared_ptr<b2World> world_;
        b2Body *worldBody_;

        CharacterVector characters_;
        CharacterPtr playerCharacter_;

        std::vector<Vector2> startPositions_;
        FixtureVector startFixtures_;
        FixtureVector goalFixtures_;

        void createPlayerCharacter();
        void updateCharacters(float dt);
    };

    inline b2World *GameLogic::world() const
    {
        return world_.get();
    }

    inline b2Body *GameLogic::worldBody() const
    {
        return worldBody_;
    }
}

#endif // MONOMI_GAME_LOGIC_HPP
