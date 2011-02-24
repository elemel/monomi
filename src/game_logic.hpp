#ifndef MONOMI_GAME_LOGIC_HPP
#define MONOMI_GAME_LOGIC_HPP

#include "category_flag.hpp"
#include "character_type.hpp"
#include "geometry.hpp"

#include <map>
#include <string>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <Box2D/Dynamics/b2World.h>

namespace monomi {
    class CharacterActor;
    class CharacterType;
    class DebugGraphics;

    class GameLogic : private boost::noncopyable {
    public:
        typedef boost::shared_ptr<CharacterType> CharacterTypePtr;
        typedef boost::shared_ptr<CharacterActor> CharacterPtr;
        typedef std::vector<CharacterPtr> CharacterVector;
        typedef std::vector<b2Fixture *> FixtureVector;

        GameLogic();

        float time() const;

        b2World *world() const;
        b2Body *worldBody() const;

        void playerCharacterName(std::string const &name);
        CharacterPtr playerCharacter() const;
        CharacterVector const &characters() const;

        void addCharacterType(CharacterTypePtr type);
        CharacterTypePtr findCharacterType(std::string const &name) const;

        void update(float dt);
        void debugDraw(DebugGraphics *graphics);

        void createPlatform(Polygon2 const &polygon);
        void createShadow(Polygon2 const &polygon);
        void createWater(Polygon2 const &polygon);

        void createStart(Circle2 const &circle);
        void createGoal(Circle2 const &circle);

        CharacterPtr createCharacter(std::string const &name,
                                     Vector2 const &position,
                                     CategoryFlag category = NEUTRAL_CATEGORY);
        void destroyCharacter(CharacterPtr character);

    private:
        typedef std::map<std::string, CharacterTypePtr> CharacterTypeMap;

        float time_;
        boost::shared_ptr<b2World> world_;
        b2Body *worldBody_;

        CharacterTypeMap characterTypes_;
        CharacterVector characters_;
        std::string playerCharacterName_;
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

    inline void GameLogic::playerCharacterName(std::string const &name)
    {
        playerCharacterName_ = name;
    }
}

#endif // MONOMI_GAME_LOGIC_HPP
