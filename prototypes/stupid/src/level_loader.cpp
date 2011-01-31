#include "level_loader.hpp"

#include "string_buffer.hpp"
#include <rapidxml.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace monomi {
    namespace {
        void traverse(rapidxml::xml_node<> *node, int depth = 0) {
            switch (node->type()) {
            case rapidxml::node_element:
                for (int i = 0; i < depth; ++i) {
                    std::cout << "  ";
                }
                std::cout << "<" << node->name();
                for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                    std::cout << " " << attr->name() << "=\"" << attr->value() << "\"";
                }
                std::cout << ">" << std::endl;
                for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling()) {
                    traverse(child, depth + 1);
                }
                for (int i = 0; i < depth; ++i) {
                    std::cout << "  ";
                }
                std::cout << "</" << node->name() << ">" << std::endl;
                break;

            case rapidxml::node_data:
            case rapidxml::node_cdata:
                for (int i = 0; i < depth; ++i) {
                    std::cout << "  ";
                }
                std::cout << node->value() << std::endl;
                break;
            }
        }
    }

    void LevelLoader::load(std::string const &path)
    {
        std::ifstream file(path.c_str());
        if (file.fail()) {
            throw std::runtime_error(StringBuffer() << "Failed to open file \"" <<
                                     path << "\".");
        }
        file.seekg(0, std::ios::end);
        long size = file.tellg();
        std::vector<char> text(size + 1);
        file.seekg(0, std::ios::beg);
        file.read(&text[0], size);
        if (file.gcount() != size) {
            throw std::runtime_error(StringBuffer() << "Failed to read " <<
                                     size << " bytes from file \"" << path << "\".");
        }
        text.back() = 0;

        rapidxml::xml_document<> doc;    // character type defaults to char
        doc.parse<0>(&text[0]);

        traverse(doc.first_node());
    }
}
