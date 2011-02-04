#include "game_logic.hpp"
#include "game_loop.hpp"
#include "string_buffer.hpp"
#include "svg_parser.hpp"

#include <SDL.h>

#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace monomi;

namespace {
    void createBodies(boost::shared_ptr<GameLogic> gameLogic,
                      std::vector<SvgParser::Element> const &elements,
                      Matrix3 const &matrix)
    {
        typedef std::vector<SvgParser::Element>::const_iterator Iterator;
        for (Iterator i = elements.begin(); i != elements.end(); ++i) {
            if (Box2 const *box = boost::get<Box2>(&i->shape)) {
                Polygon2 polygon(*box);
                Polygon2 transformedPolygon = transform(polygon, matrix * i->matrix);
                if (transformedPolygon.clockwise()) {
                    transformedPolygon.reverse();
                }
                gameLogic->createPolygonBody(transformedPolygon);
            } else if (Circle2 const *circle = boost::get<Circle2>(&i->shape)) {
                Circle2 transformedCircle = transform(*circle, matrix * i->matrix);
                gameLogic->createCircleBody(transformedCircle);
            } else if (Polygon2 const *polygon = boost::get<Polygon2>(&i->shape)) {
                Polygon2 transformedPolygon = transform(*polygon, matrix * i->matrix);
                if (transformedPolygon.clockwise()) {
                    transformedPolygon.reverse();
                }
                gameLogic->createPolygonBody(transformedPolygon);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    try {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) == -1) {
            throw std::runtime_error(StringBuffer() << "Failed to initialize SDL: " << SDL_GetError());
        }

        if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) == -1) {
            std::cerr << "WARNING: Failed to enable double buffering: "
                      << SDL_GetError() << std::endl;
        }
        SDL_Surface *videoSurface = SDL_SetVideoMode(0, 0, 0, SDL_OPENGL | SDL_FULLSCREEN);
        if (videoSurface == 0) {
            throw std::runtime_error(StringBuffer() << "Failed to set SDL video mode: " << SDL_GetError());
        }
        if (SDL_GL_SetSwapInterval(1) == -1) {
            std::cerr << "WARNING: Failed to enable vertical sync: "
                      << SDL_GetError() << std::endl;
        }

        boost::shared_ptr<GameLogic> gameLogic(new GameLogic);

        boost::shared_ptr<SvgParser> svgParser(new SvgParser);
        std::vector<SvgParser::Element> elements;
        svgParser->parse(argc == 2 ? argv[1] : "", elements);
        Matrix3 matrix(0.01f, 0.0f, 0.0f,
                       0.0f, -0.01f, 0.0f);
        createBodies(gameLogic, elements, matrix);

        GameLoop gameLoop(gameLogic);
        gameLoop.run();

        SDL_Quit();
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
