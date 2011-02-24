#include "character_type.hpp"
#include "color.hpp"
#include "game_logic.hpp"
#include "game_loop.hpp"
#include "string_buffer.hpp"
#include "svg_parser.hpp"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <SDL.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

using namespace monomi;

namespace {
    template <typename T>
    T get(std::string const &path, boost::property_tree::ptree const &values,
          boost::property_tree::ptree const &defaults)
    {
        boost::optional<T> result = values.get_optional<T>(path);
        return result ? *result : defaults.get<T>(path);
    }

    void loadCharacterType(std::string const &name,
                           boost::property_tree::ptree const &tree,
                           boost::shared_ptr<GameLogic> gameLogic)
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

        CharacterTechniqueFlagSet techniqueFlags;
        techniqueFlags.set(CHARACTER_CEILING_RUN_TECHNIQUE, get<bool>("ceiling-run-technique", values, defaults));
        techniqueFlags.set(CHARACTER_DOUBLE_JUMP_TECHNIQUE, get<bool>("double-jump-technique", values, defaults));
        techniqueFlags.set(CHARACTER_GLIDE_TECHNIQUE, get<bool>("glide-technique", values, defaults));
        techniqueFlags.set(CHARACTER_SLIDE_TECHNIQUE, get<bool>("slide-technique", values, defaults));
        techniqueFlags.set(CHARACTER_STOMP_TECHNIQUE, get<bool>("stomp-technique", values, defaults));
        techniqueFlags.set(CHARACTER_TELEPORT_TECHNIQUE, get<bool>("teleport-technique", values, defaults));
        techniqueFlags.set(CHARACTER_TRIPLE_JUMP_TECHNIQUE, get<bool>("triple-jump-technique", values, defaults));
        techniqueFlags.set(CHARACTER_WALL_JUMP_TECHNIQUE, get<bool>("wall-jump-technique", values, defaults));
        techniqueFlags.set(CHARACTER_WALL_RUN_TECHNIQUE, get<bool>("wall-run-technique", values, defaults));
        techniqueFlags.set(CHARACTER_WALL_SLIDE_TECHNIQUE, get<bool>("wall-slide-technique", values, defaults));
        type->techniqueFlags(techniqueFlags);

        CharacterToolFlagSet toolFlags;
        toolFlags.set(CHARACTER_AIR_SKIN_TOOL, get<bool>("air-skin-tool", values, defaults));
        toolFlags.set(CHARACTER_BAMBOO_FLUTE_TOOL, get<bool>("bamboo-flute-tool", values, defaults));
        toolFlags.set(CHARACTER_GRAPPLING_HOOK_TOOL, get<bool>("grappling-hook-tool", values, defaults));
        toolFlags.set(CHARACTER_IRON_FAN_TOOL, get<bool>("iron-fan-tool", values, defaults));
        toolFlags.set(CHARACTER_SMOKE_BOMBS_TOOL, get<bool>("smoke-bombs-tool", values, defaults));
        toolFlags.set(CHARACTER_STRAW_BASKET_TOOL, get<bool>("straw-basket-tool", values, defaults));
        toolFlags.set(CHARACTER_THROWING_STARS_TOOL, get<bool>("throwing-stars-tool", values, defaults));
        toolFlags.set(CHARACTER_TIGER_CLAWS_TOOL, get<bool>("tiger-claws-tool", values, defaults));
        type->toolFlags(toolFlags);

        gameLogic->addCharacterType(type);
    }

    void loadCharacterTypes(std::istream &config, boost::shared_ptr<GameLogic> gameLogic)
    {
        boost::property_tree::ptree tree;
        boost::property_tree::read_ini(config, tree);

        loadCharacterType("air-master", tree, gameLogic);
        loadCharacterType("earth-master", tree, gameLogic);
        loadCharacterType("fire-master", tree, gameLogic);
        loadCharacterType("grandmaster", tree, gameLogic);
        loadCharacterType("kunoichi", tree, gameLogic);
        loadCharacterType("ninja", tree, gameLogic);
        loadCharacterType("samurai", tree, gameLogic);
        loadCharacterType("void-master", tree, gameLogic);
        loadCharacterType("water-master", tree, gameLogic);
    }

    void createCircleGameObject(boost::shared_ptr<GameLogic> gameLogic,
                          Circle2 const &circle, ColorName colorName)
    {
        switch (colorName) {
        case LIME_COLOR:
            gameLogic->createStart(circle);
            break;

        case RED_COLOR:
            gameLogic->createGoal(circle);
            break;

        default:
            break;
        }
    }

    void createPolygonGameObject(boost::shared_ptr<GameLogic> gameLogic,
                          Polygon2 const &polygon, ColorName colorName)
    {
        switch (colorName) {
        case BLUE_COLOR:
            gameLogic->createWater(polygon);
            break;

        case FUCHSIA_COLOR:
            gameLogic->createShadow(polygon);
            break;

        case YELLOW_COLOR:
            gameLogic->createPlatform(polygon);
            break;

        default:
            break;
        }
    }

    void createGameObjects(boost::shared_ptr<GameLogic> gameLogic,
                           std::vector<SvgParser::Element> const &elements,
                           Matrix3 const &matrix)
    {
        typedef std::vector<SvgParser::Element>::const_iterator Iterator;
        for (Iterator i = elements.begin(); i != elements.end(); ++i) {
            ColorName colorName = i->color.name();
            if (Box2 const *box = boost::get<Box2>(&i->shape)) {
                Polygon2 polygon(*box);
                Polygon2 transformedPolygon = transform(polygon, matrix * i->matrix);
                if (transformedPolygon.clockwise()) {
                    transformedPolygon.reverse();
                }
                createPolygonGameObject(gameLogic, transformedPolygon, colorName);
            } else if (Circle2 const *circle = boost::get<Circle2>(&i->shape)) {
                Circle2 transformedCircle = transform(*circle, matrix * i->matrix);
                createCircleGameObject(gameLogic, transformedCircle, colorName);
            } else if (Polygon2 const *polygon = boost::get<Polygon2>(&i->shape)) {
                Polygon2 transformedPolygon = transform(*polygon, matrix * i->matrix);
                if (transformedPolygon.clockwise()) {
                    transformedPolygon.reverse();
                }
                createPolygonGameObject(gameLogic, transformedPolygon, colorName);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    try {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) == -1) {
            throw std::runtime_error(StringBuffer() <<
                                     "Failed to initialize SDL: " <<
                                     SDL_GetError());
        }

        if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) == -1) {
            std::cerr << "WARNING: Failed to enable double buffering: "
                      << SDL_GetError() << std::endl;
        }
        SDL_Surface *videoSurface = SDL_SetVideoMode(0, 0, 0, SDL_OPENGL | SDL_FULLSCREEN);
        if (videoSurface == 0) {
            throw std::runtime_error(StringBuffer() <<
                                     "Failed to set SDL video mode: " <<
                                     SDL_GetError());
        }
        if (SDL_GL_SetSwapInterval(1) == -1) {
            std::cerr << "WARNING: Failed to enable vertical sync: "
                      << SDL_GetError() << std::endl;
        }

        boost::shared_ptr<GameLogic> gameLogic(new GameLogic);

        std::ifstream characterConfig("../config/character.ini");
        loadCharacterTypes(characterConfig, gameLogic);
        std::string characterName = (argc >= 3) ? argv[2] : "grandmaster";
        if (gameLogic->findCharacterType(characterName)) {
            gameLogic->playerCharacterName(characterName);
        } else {
            std::cerr << "WARNING: Invalid character name \"" << characterName
                      << "\"." << std::endl;
        }

        gameLogic->createCharacter("samurai", Vector2(7.0f, 0.0f), ENEMY_CATEGORY);

        std::string levelName = (argc >= 2) ? argv[1] : "../assets/levels/sandbox.svg";

        boost::shared_ptr<SvgParser> svgParser(new SvgParser);
        SvgParser::ElementVector const &elements = svgParser->parse(levelName);
        Matrix3 matrix(0.01f, 0.0f, 0.0f,
                       0.0f, -0.01f, 0.0f);
        createGameObjects(gameLogic, elements, matrix);

        GameLoop gameLoop(gameLogic);
        gameLoop.run();
    } catch (std::exception const &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    SDL_Quit();
    return 0;
}
