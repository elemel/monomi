#include "svg_parser.hpp"

#include "string_buffer.hpp"
#include "svg_transform_parser.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace monomi {
    namespace {
        char const *findAttribute(rapidxml::xml_node<> *node, char const *name)
        {
            for (rapidxml::xml_attribute<> *attr = node->first_attribute();
                 attr; attr = attr->next_attribute())
            {
                if (strcmp(attr->name(), name) == 0) {
                    return attr->value();
                }
            }
            return 0;
        }

        float parseAttribute(rapidxml::xml_node<> *node,
                             char const *name, float defaultValue)
        {
            if (char const *value = findAttribute(node, name)) {
                return atof(value);
            } else {
                return defaultValue;
            }
        }
    }

    void SvgParser::parse(std::string const &path, std::vector<Element> &elements)
    {
        std::ifstream file(path.c_str());
        if (file.fail()) {
            throw std::runtime_error(StringBuffer() <<
                                     "Failed to open file \"" << path <<
                                     "\".");
        }
        file.seekg(0, std::ios::end);
        long size = file.tellg();
        std::vector<char> text(size + 1); // Reserve space for null terminator.
        file.seekg(0, std::ios::beg);
        file.read(&text[0], size);
        if (file.gcount() != size) {
            throw std::runtime_error(StringBuffer() << "Failed to read " <<
                                     size << " bytes from file \"" << path <<
                                     "\".");
        }
        text.back() = 0; // Null terminator.

        rapidxml::xml_document<> doc;
        doc.parse<0>(&text[0]);

        parseNode(doc.first_node(), Matrix3(), elements);
    }

    void SvgParser::parseNode(rapidxml::xml_node<> *node,
                              Matrix3 const &parentMatrix,
                              std::vector<Element> &elements)
    {
        switch (node->type()) {
        case rapidxml::node_element:
            {
                Matrix3 matrix;
                if (char const *transform = findAttribute(node, "transform")) {
                    matrix = SvgTransformParser().parse(transform);
                }
                matrix = parentMatrix * matrix;

                if (strcmp(node->name(), "path") == 0) {
                    if (char const *type = findAttribute(node, "sodipodi:type")) {
                        if (strcmp(type, "arc") == 0) {
                            float cx = parseAttribute(node, "sodipodi:cx", 0.0f);
                            float cy = parseAttribute(node, "sodipodi:cy", 0.0f);
                            float rx = parseAttribute(node, "sodipodi:rx", 1.0f);
                            float ry = parseAttribute(node, "sodipodi:ry", 1.0f);

                            Vector2 center(cx, cy);
                            float radius = 0.5f * (rx + ry);
                            Circle2 circle(center, radius);

                            Element element;
                            element.matrix = matrix;
                            element.shape = circle;

                            elements.push_back(element);
                        }
                    }
                } else if (strcmp(node->name(), "rect") == 0) {
                    float x = parseAttribute(node, "x", 0.0f);
                    float y = parseAttribute(node, "y", 0.0f);
                    float width = parseAttribute(node, "width", 1.0f);
                    float height = parseAttribute(node, "height", 1.0f);

                    Vector2 p1(x, y);
                    Vector2 p2(x + width, y + height);
                    Box2 box(p1, p2);

                    Element element;
                    element.matrix = matrix;
                    element.shape = box;

                    elements.push_back(element);
                }

                for (rapidxml::xml_node<> *child = node->first_node(); child;
                     child = child->next_sibling())
                {
                    parseNode(child, matrix, elements);
                }
            }
            break;

        case rapidxml::node_data:
        case rapidxml::node_cdata:
            break;
        }
    }
}
