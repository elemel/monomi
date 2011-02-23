#ifndef MONOMI_SVG_PARSER_HPP
#define MONOMI_SVG_PARSER_HPP

#include "color.hpp"
#include "geometry.hpp"
#include "svg_path_parser.hpp"
#include "svg_style_parser.hpp"
#include "svg_transform_parser.hpp"

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>
#include <rapidxml.hpp>

namespace monomi {
    class SvgParser {
    public:
        typedef boost::variant<Box2, Circle2, Polygon2> Shape2;

        struct Element {
            Matrix3 matrix;
            Shape2 shape;
            Color3 color;
        };

        typedef std::vector<Element> ElementVector;

        ElementVector const &parse(std::string const &path);

    private:
        SvgPathParser pathParser_;
        SvgStyleParser styleParser_;
        SvgTransformParser transformParser_;
        ElementVector elements_;

        void parseNode(rapidxml::xml_node<> *node,
                       Matrix3 const &parentMatrix);
        void parseElement(rapidxml::xml_node<> *node,
                          Matrix3 const &parentMatrix);
        void parseArcElement(rapidxml::xml_node<> *node,
                             Matrix3 const &matrix);
        void parsePathElement(rapidxml::xml_node<> *node,
                              Matrix3 const &matrix);
        void parseRectElement(rapidxml::xml_node<> *node,
                              Matrix3 const &matrix);

        Color3 parseFill(rapidxml::xml_node<> *node);
        Color3 parseColor(std::string const &str);
        int parseHexDigit(char digit);
    };
}

#endif // MOMOMI_SVG_PARSER_HPP
