#include "character_config_loader.hpp"
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
#include <boost/timer.hpp>

using namespace monomi;

namespace {
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
        boost::timer t1;

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

        std::cerr << "DEBUG: Initialized SDL in " << t1.elapsed() << " second(s)." << std::endl;

        boost::shared_ptr<GameLogic> gameLogic(new GameLogic);

        CharacterConfigLoader(*gameLogic).load("../config/character.ini");

        std::string characterName = (argc >= 3) ? argv[2] : "grandmaster";
        if (gameLogic->findCharacterType(characterName)) {
            gameLogic->playerCharacterName(characterName);
        } else {
            std::cerr << "WARNING: Invalid character name \"" << characterName
                      << "\"." << std::endl;
        }

        boost::timer t2;

        std::string levelName = (argc >= 2) ? argv[1] : "../assets/levels/sandbox.svg";
        SvgParser svgParser;
        SvgParser::ElementVector const &elements = svgParser.parse(levelName);

        std::cerr << "DEBUG: Loaded level in " << t2.elapsed() << " second(s)." << std::endl;

        Matrix3 matrix(0.01f, 0.0f, 0.0f,
                       0.0f, -0.01f, 0.0f);
        createGameObjects(gameLogic, elements, matrix);

        gameLogic->createCharacter("samurai", Vector2(7.0f, 0.0f), ENEMY_CATEGORY);

        GameLoop gameLoop(gameLogic);
        gameLoop.run();
    } catch (std::exception const &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    SDL_Quit();
    return 0;
}
