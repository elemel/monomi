#include "level_loader.hpp"

#include "game_logic.hpp"

#include <boost/timer.hpp>

namespace monomi {
    void LevelLoader::load(std::string const &path)
    {
        boost::timer t2;

        SvgParser svgParser;
        SvgParser::ElementVector const &elements = svgParser.parse(path);

        Matrix3 matrix(0.01f, 0.0f, 0.0f,
                       0.0f, -0.01f, 0.0f);
        createGameObjects(elements, matrix);

        std::cerr << "DEBUG: Loaded level in " << t2.elapsed() << " second(s)." << std::endl;
    }

    void LevelLoader::createCircleGameObject(Circle2 const &circle, ColorName colorName)
    {
        switch (colorName) {
        case LIME_COLOR:
            gameLogic_->createStart(circle);
            break;

        case RED_COLOR:
            gameLogic_->createGoal(circle);
            break;

        default:
            break;
        }
    }

    void LevelLoader::createPolygonGameObject(Polygon2 const &polygon, ColorName colorName)
    {
        switch (colorName) {
        case BLUE_COLOR:
            gameLogic_->createWater(polygon);
            break;

        case FUCHSIA_COLOR:
            gameLogic_->createShadow(polygon);
            break;

        case YELLOW_COLOR:
            gameLogic_->createPlatform(polygon);
            break;

        default:
            break;
        }
    }

    void LevelLoader::createGameObjects(std::vector<SvgParser::Element> const &elements,
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
                createPolygonGameObject(transformedPolygon, colorName);
            } else if (Circle2 const *circle = boost::get<Circle2>(&i->shape)) {
                Circle2 transformedCircle = transform(*circle, matrix * i->matrix);
                createCircleGameObject(transformedCircle, colorName);
            } else if (Polygon2 const *polygon = boost::get<Polygon2>(&i->shape)) {
                Polygon2 transformedPolygon = transform(*polygon, matrix * i->matrix);
                if (transformedPolygon.clockwise()) {
                    transformedPolygon.reverse();
                }
                createPolygonGameObject(transformedPolygon, colorName);
            }
        }
    }
}
