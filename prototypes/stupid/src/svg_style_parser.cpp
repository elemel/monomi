#include "svg_style_parser.hpp"

#include "string_buffer.hpp"

namespace monomi {
    SvgStyleParser::SvgStyleParser() :
        separator_(" \t\r\n,", ":;")
    { }

    SvgStyleParser::DeclarationMap const &SvgStyleParser::parse(std::string const &str)
    {
        declarations_.clear();
        Matrix3 result;
        Tokenizer tokenizer(str, separator_);
        State state = BEFORE_PROPERTY_STATE;
        for (Tokenizer::iterator i = tokenizer.begin(); i != tokenizer.end();
             ++i)
        {
            token_ = *i;
            if (token_ == ":") {
                state = BEFORE_VALUE_STATE;
            } else if (token_ == ";") {
                declarations_[property_] = value_;
                state = BEFORE_PROPERTY_STATE;
            } else {
                if (state == BEFORE_PROPERTY_STATE) {
                    property_ = token_;
                    state = AFTER_PROPERTY_STATE;
                } else if (state == BEFORE_VALUE_STATE) {
                    value_ = token_;
                    state = AFTER_VALUE_STATE;
                }
            }
        }
        if (state == AFTER_VALUE_STATE) {
            declarations_[property_] = value_;
        }
        return declarations_;
    }
}
