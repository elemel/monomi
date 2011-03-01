#include "character_config_loader.hpp"

#include "game_logic.hpp"

#include <boost/timer.hpp>

namespace monomi {
    namespace {
        template <typename T>
        T get(std::string const &path, boost::property_tree::ptree const &values,
              boost::property_tree::ptree const &defaults)
        {
            boost::optional<T> result = values.get_optional<T>(path);
            return result ? *result : defaults.get<T>(path);
        }
    }

    CharacterConfigLoader::CharacterConfigLoader(GameLogic &gameLogic) :
        gameLogic_(&gameLogic)
    { }

    void CharacterConfigLoader::load(std::string const &path)
    {
        boost::timer t1;

        std::ifstream config(path.c_str());
        boost::property_tree::ptree tree;
        boost::property_tree::read_ini(config, tree);

        loadCharacterType("air-master", tree);
        loadCharacterType("earth-master", tree);
        loadCharacterType("fire-master", tree);
        loadCharacterType("grandmaster", tree);
        loadCharacterType("kunoichi", tree);
        loadCharacterType("ninja", tree);
        loadCharacterType("samurai", tree);
        loadCharacterType("void-master", tree);
        loadCharacterType("water-master", tree);

        std::cerr << "DEBUG: Loaded character config in " << t1.elapsed() << " second(s)." << std::endl;
    }

    void CharacterConfigLoader::loadCharacterType(std::string const &name,
                                                  boost::property_tree::ptree const &tree)
    {
        boost::optional<boost::property_tree::ptree const &> optionalValues = tree.get_child_optional(name);
        boost::property_tree::ptree emptyValues;
        boost::property_tree::ptree const &values = optionalValues ? *optionalValues : emptyValues;
        boost::property_tree::ptree const &defaults = tree.get_child("defaults");

        GameLogic::CharacterTypePtr type(new CharacterType);
        type->name(name);

        type->ceilingRunAcceleration(get<float>("ceiling-run-acceleration", values, defaults));
        type->ceilingRunVelocity(get<float>("ceiling-run-velocity", values, defaults));
        type->fallAcceleration(get<float>("fall-acceleration", values, defaults));
        type->fallVelocity(get<float>("fall-velocity", values, defaults));
        type->jumpVelocity(get<float>("jump-velocity", values, defaults));
        type->runAcceleration(get<float>("run-acceleration", values, defaults));
        type->runVelocity(get<float>("run-velocity", values, defaults));
        type->stompAcceleration(get<float>("stomp-acceleration", values, defaults));
        type->stompVelocity(get<float>("stomp-velocity", values, defaults));
        type->walkAcceleration(get<float>("walk-acceleration", values, defaults));
        type->walkVelocity(get<float>("walk-velocity", values, defaults));
        type->wallJumpVelocity(get<float>("wall-jump-velocity", values, defaults));
        type->wallJumpAngle(get<float>("wall-jump-angle", values, defaults));
        type->wallRunAcceleration(get<float>("wall-run-acceleration", values, defaults));
        type->wallRunVelocity(get<float>("wall-run-velocity", values, defaults));
        type->wallSlideAcceleration(get<float>("wall-slide-acceleration", values, defaults));
        type->wallSlideVelocity(get<float>("wall-slide-velocity", values, defaults));

        CharacterTechniqueSet techniques;
        techniques.set(CHARACTER_CEILING_RUN_TECHNIQUE, get<bool>("ceiling-run-technique", values, defaults));
        techniques.set(CHARACTER_DOUBLE_JUMP_TECHNIQUE, get<bool>("double-jump-technique", values, defaults));
        techniques.set(CHARACTER_GLIDE_TECHNIQUE, get<bool>("glide-technique", values, defaults));
        techniques.set(CHARACTER_SLIDE_TECHNIQUE, get<bool>("slide-technique", values, defaults));
        techniques.set(CHARACTER_STOMP_TECHNIQUE, get<bool>("stomp-technique", values, defaults));
        techniques.set(CHARACTER_TELEPORT_TECHNIQUE, get<bool>("teleport-technique", values, defaults));
        techniques.set(CHARACTER_TRIPLE_JUMP_TECHNIQUE, get<bool>("triple-jump-technique", values, defaults));
        techniques.set(CHARACTER_WALL_JUMP_TECHNIQUE, get<bool>("wall-jump-technique", values, defaults));
        techniques.set(CHARACTER_WALL_RUN_TECHNIQUE, get<bool>("wall-run-technique", values, defaults));
        techniques.set(CHARACTER_WALL_SLIDE_TECHNIQUE, get<bool>("wall-slide-technique", values, defaults));
        type->techniques(techniques);

        CharacterToolSet tools;
        tools.set(CHARACTER_AIR_SKIN_TOOL, get<bool>("air-skin-tool", values, defaults));
        tools.set(CHARACTER_BAMBOO_FLUTE_TOOL, get<bool>("bamboo-flute-tool", values, defaults));
        tools.set(CHARACTER_GRAPPLING_HOOK_TOOL, get<bool>("grappling-hook-tool", values, defaults));
        tools.set(CHARACTER_IRON_FAN_TOOL, get<bool>("iron-fan-tool", values, defaults));
        tools.set(CHARACTER_SMOKE_BOMBS_TOOL, get<bool>("smoke-bombs-tool", values, defaults));
        tools.set(CHARACTER_STRAW_BASKET_TOOL, get<bool>("straw-basket-tool", values, defaults));
        tools.set(CHARACTER_THROWING_STARS_TOOL, get<bool>("throwing-stars-tool", values, defaults));
        tools.set(CHARACTER_TIGER_CLAWS_TOOL, get<bool>("tiger-claws-tool", values, defaults));
        type->tools(tools);

        gameLogic_->addCharacterType(type);
    }
}
