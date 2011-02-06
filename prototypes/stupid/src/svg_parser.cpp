#include "svg_parser.hpp"

#include "string_buffer.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace monomi {
    namespace {
        char const *stripPrefix(char const *name) {
            if (char const *strippedName = strchr(name, ':')) {
                return strippedName + 1;
            } else {
                return name;
            }
        }

        char const *findAttribute(rapidxml::xml_node<> *node, char const *name)
        {
            for (rapidxml::xml_attribute<> *attr = node->first_attribute();
                 attr; attr = attr->next_attribute())
            {
                if (strcmp(stripPrefix(attr->name()), name) == 0) {
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

    SvgParser::ElementVector const &SvgParser::parse(std::string const &path)
    {
        elements_.clear();
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

        parseNode(doc.first_node(), Matrix3());
        return elements_;
    }

    void SvgParser::parseNode(rapidxml::xml_node<> *node,
                              Matrix3 const &parentMatrix)
    {
        switch (node->type()) {
        case rapidxml::node_element:
            {
                Matrix3 matrix;
                if (char const *transform = findAttribute(node, "transform")) {
                    matrix = transformParser_.parse(transform);
                }
                matrix = parentMatrix * matrix;

                if (strcmp(node->name(), "path") == 0) {
                    if (char const *type = findAttribute(node, "type")) {
                        if (strcmp(type, "arc") == 0) {
                            float cx = parseAttribute(node, "cx", 0.0f);
                            float cy = parseAttribute(node, "cy", 0.0f);
                            float rx = parseAttribute(node, "rx", 1.0f);
                            float ry = parseAttribute(node, "ry", 1.0f);

                            Vector2 center(cx, cy);
                            float radius = 0.5f * (rx + ry);
                            Circle2 circle(center, radius);

                            Element element;
                            element.matrix = matrix;
                            element.shape = circle;
                            element.color = parseFill(node);

                            elements_.push_back(element);
                        }
                    } else {
                        if (char const *d = findAttribute(node, "d")) {
                            Polygon2 polygon = pathParser_.parse(d);

                            Element element;
                            element.matrix = matrix;
                            element.shape = polygon;
                            element.color = parseFill(node);

                            elements_.push_back(element);
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
                    element.color = parseFill(node);

                    elements_.push_back(element);
                }

                for (rapidxml::xml_node<> *child = node->first_node(); child;
                     child = child->next_sibling())
                {
                    parseNode(child, matrix);
                }
            }
            break;

        case rapidxml::node_data:
        case rapidxml::node_cdata:
            break;

        default:
            break;
        }
    }

    Color3 SvgParser::parseFill(rapidxml::xml_node<> *node)
    {
        if (char const *type = findAttribute(node, "style")) {
            SvgStyleParser::DeclarationMap const &declarations = styleParser_.parse(type);
            SvgStyleParser::DeclarationMap::const_iterator i = declarations.find("fill");
            if (i != declarations.end()) {
                return parseColor(i->second);
            }
        }
        return Color3();
    }

    Color3 SvgParser::parseColor(std::string const &str)
    {
        if (str.size() == 7 && str[0] == '#') {
            for (std::size_t i = 1; i < str.size(); ++i) {
                if (parseHexDigit(str[i]) == -1) {
                    return Color3();
                }
            }
            int red = 16 * parseHexDigit(str[1]) + parseHexDigit(str[2]);
            int green = 16 * parseHexDigit(str[3]) + parseHexDigit(str[4]);
            int blue = 16 * parseHexDigit(str[5]) + parseHexDigit(str[6]);
            return Color3(red, green, blue);
        }
        return Color3();
    }

    int SvgParser::parseHexDigit(char digit)
    {
        if ('0' <= digit && digit <= '9') {
            return digit - '0';
        } else if ('A' <= digit && digit <= 'F') {
            return 10 + digit - 'A';
        } else if ('a' <= digit && digit <= 'f') {
            return 10 + digit - 'a';
        } else {
            return -1;
        }
    }
}
