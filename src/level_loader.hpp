#ifndef MONOMI_LEVEL_LOADER_HPP
#define MONOMI_LEVEL_LOADER_HPP

#include "color.hpp"
#include "geometry.hpp"
#include "svg_parser.hpp"

#include <string>
#include <vector>

namespace monomi {
    class GameLogic;

    class LevelLoader {
    public:
        explicit LevelLoader(GameLogic& gameLogic);

        void load(std::string const &path);

    private:
        GameLogic *gameLogic_;

        void createCircleGameObject(Circle2 const &circle, ColorName colorName);
        void createPolygonGameObject(Polygon2 const &polygon, ColorName colorName);
        void createGameObjects(std::vector<SvgParser::Element> const &elements,
                               Matrix3 const &matrix);
    };

    inline LevelLoader::LevelLoader(GameLogic& gameLogic) :
        gameLogic_(&gameLogic)
    { }
}

#endif // MONOMI_LEVEL_LOADER_HPP
