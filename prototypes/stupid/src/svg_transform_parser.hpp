#ifndef MONOMI_SVG_TRANSFORM_PARSER_HPP
#define MONOMI_SVG_TRANSFORM_PARSER_HPP

#include "geometry.hpp"

#include <boost/tokenizer.hpp>

namespace monomi {
    class SvgTransformParser {
    public:
        SvgTransformParser();

        Matrix3 parse(std::string const &str);

    private:
        typedef boost::char_separator<char> Separator;
        typedef boost::tokenizer<Separator> Tokenizer;

        enum State {
            beforeTypeState,
            afterTypeState,
            inArgsState
        };

        Separator separator_;
        std::string token_;
        std::string type_;
        std::vector<float> args_;

        void debugPrintTransform();
        Matrix3 parseTransform();
        Matrix3 parseMatrixTransform();
        Matrix3 parseRotateTransform();
        Matrix3 parseScaleTransform();
        Matrix3 parseTranslateTransform();
    };
}

#endif // MONOMI_SVG_TRANSFORM_PARSER_HPP
