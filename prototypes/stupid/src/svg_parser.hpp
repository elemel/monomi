#ifndef MONOMI_SVG_PARSER_HPP
#define MONOMI_SVG_PARSER_HPP

#include "color.hpp"
#include "geometry.hpp"

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

        void parse(std::string const &path, std::vector<Element> &elements);

    private:
        void parseNode(rapidxml::xml_node<> *node,
                       Matrix3 const &parentMatrix,
                       std::vector<Element> &elements);
    };
}

#endif // MOMOMI_SVG_PARSER_HPP
