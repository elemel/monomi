#ifndef MONOMI_SVG_STYLE_PARSER_HPP
#define MONOMI_SVG_STYLE_PARSER_HPP

#include "geometry.hpp"

#include <map>
#include <string>
#include <boost/tokenizer.hpp>

namespace monomi {
    class SvgStyleParser {
    public:
        typedef std::map<std::string, std::string> DeclarationMap;

        SvgStyleParser();

        DeclarationMap const &parse(std::string const &str);

    private:
        typedef boost::char_separator<char> Separator;
        typedef boost::tokenizer<Separator> Tokenizer;

        enum State {
            BEFORE_PROPERTY_STATE,
            AFTER_PROPERTY_STATE,
            BEFORE_VALUE_STATE,
            AFTER_VALUE_STATE,
            
            STATE_COUNT
        };

        Separator separator_;
        std::string token_;
        std::string property_;
        std::string value_;
        DeclarationMap declarations_; 
    };
}

#endif // MONOMI_SVG_STYLE_PARSER_HPP
