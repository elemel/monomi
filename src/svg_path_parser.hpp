#ifndef MONOMI_SVG_PATH_PARSER_HPP
#define MONOMI_SVG_PATH_PARSER_HPP

#include "geometry.hpp"

#include <boost/tokenizer.hpp>

namespace monomi {
    class SvgPathParser {
    public:
        SvgPathParser();

        Polygon2 parse(std::string const &str);

    private:
        typedef boost::char_separator<char> Separator;
        typedef boost::tokenizer<Separator> Tokenizer;

        Separator separator_;
        std::string token_;
        char command_;
        std::vector<float> args_;

        void parseCommand(Polygon2 &polygon);
        void parseAbsoluteMovetoCommand(Polygon2 &polygon);
        void parseRelativeMovetoCommand(Polygon2 &polygon);
        void parseAbsoluteLinetoCommand(Polygon2 &polygon);
        void parseRelativeLinetoCommand(Polygon2 &polygon);
    };
}

#endif // MONOMI_SVG_PATH_PARSER_HPP
