#include "svg_transform_parser.hpp"

#include "string_buffer.hpp"

namespace monomi {
    SvgTransformParser::SvgTransformParser() :
        separator_(" \t\r\n,", "()")
    { }

    Matrix3 SvgTransformParser::parse(std::string const &str)
    {
        Matrix3 result;
        Tokenizer tokenizer(str, separator_);
        State state = beforeTypeState;
        for (Tokenizer::iterator i = tokenizer.begin(); i != tokenizer.end();
             ++i)
        {
            token_ = *i;
            if (token_ == "(") {
                args_.clear();
                state = inArgsState;
            } else if (token_ == ")") {
                // debugPrintTransform();
                result *= parseTransform();
                state = beforeTypeState;
            } else {
                if (state == beforeTypeState) {
                    type_ = token_;
                    state = afterTypeState;
                } else if (state == inArgsState) {
                    args_.push_back(atof(token_.c_str()));
                }
            }
        }
        return result;
    }

    void SvgTransformParser::debugPrintTransform()
    {
        std::cerr << "DEBUG: Tokenized SVG transform: " << type_ << "(";
        for (std::size_t j = 0; j < args_.size(); ++j) {
            if (j) {
                std::cerr << ", ";
            }
            std::cerr << args_[j];
        }
        std::cerr << ")" << std::endl;
    }

    Matrix3 SvgTransformParser::parseTransform()
    {
        if (type_ == "matrix") {
            return parseMatrixTransform();
        } else if (type_ == "rotate") {
            return parseRotateTransform();
        } else if (type_ == "scale") {
            return parseScaleTransform();
        } else if (type_ == "translate") {
            return parseTranslateTransform();
        } else {
            throw std::runtime_error(StringBuffer() << "Invalid SVG transform type \"" << type_ << "\".");
        }
    }

    Matrix3 SvgTransformParser::parseMatrixTransform()
    {
        if (args_.size() == 6) {
            return Matrix3(args_[0], args_[2], args_[4],
                           args_[1], args_[3], args_[5]);
        } else {
            throw std::runtime_error(StringBuffer() << "Invalid argument count for SVG transform type \"" << type_ << "\".");
        }
    }

    Matrix3 SvgTransformParser::parseRotateTransform()
    {
        if (args_.size() == 1) {
            return Matrix3(std::cos(args_[0]), -std::sin(args_[0]), 0.0f,
                           std::sin(args_[0]), std::cos(args_[0]), 0.0f);
        } else if (args_.size() == 3) {
            return (Matrix3(1.0f, 0.0f, args_[1],
                            0.0f, 1.0f, args_[2]) *
                    Matrix3(std::cos(args_[0]), -std::sin(args_[0]), 0.0f,
                            std::sin(args_[0]), std::cos(args_[0]), 0.0f) *
                    Matrix3(1.0f, 0.0f, -args_[1],
                            0.0f, 1.0f, -args_[2]));
        } else {
            throw std::runtime_error(StringBuffer() << "Invalid argument count for SVG transform type \"" << type_ << "\".");
        }
    }

    Matrix3 SvgTransformParser::parseScaleTransform()
    {
        if (args_.size() == 1) {
            return Matrix3(args_[0], 0.0f, 0.0f,
                           0.0f, args_[0], 0.0f);
        } else if (args_.size() == 2) {
            return Matrix3(args_[0], 0.0f, 0.0f,
                           0.0f, args_[1], 0.0f);
        } else {
            throw std::runtime_error(StringBuffer() << "Invalid argument count for SVG transform type \"" << type_ << "\".");
        }
    }

    Matrix3 SvgTransformParser::parseTranslateTransform()
    {
        if (args_.size() == 1) {
            return Matrix3(1.0f, 0.0f, args_[0],
                           0.0f, 1.0f, 0.0f);
        } else if (args_.size() == 2) {
            return Matrix3(1.0f, 0.0f, args_[0],
                           0.0f, 1.0f, args_[1]);
        } else {
            throw std::runtime_error(StringBuffer() << "Invalid argument count for SVG transform type \"" << type_ << "\".");
        }
    }
}
