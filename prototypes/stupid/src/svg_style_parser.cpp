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
        State state = beforePropertyState;
        for (Tokenizer::iterator i = tokenizer.begin(); i != tokenizer.end();
             ++i)
        {
            token_ = *i;
            if (token_ == ":") {
                state = beforeValueState;
            } else if (token_ == ";") {
                declarations_[property_] = value_;
                state = beforePropertyState;
            } else {
                if (state == beforePropertyState) {
                    property_ = token_;
                    state = afterPropertyState;
                } else if (state == beforeValueState) {
                    value_ = token_;
                    state = afterValueState;
                }
            }
        }
        if (state == afterValueState) {
            declarations_[property_] = value_;
        }
        return declarations_;
    }
}
