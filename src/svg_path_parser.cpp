#include "svg_path_parser.hpp"

#include "string_buffer.hpp"

namespace monomi {
    SvgPathParser::SvgPathParser() :
        separator_(" \t\r\n,", "MmLlHhVvCcSsQqTtAaZz")
    { }

    Polygon2 SvgPathParser::parse(std::string const &str)
    {
        Polygon2 result;
        Tokenizer tokenizer(str, separator_);
        command_ = 0;
        for (Tokenizer::iterator i = tokenizer.begin(); i != tokenizer.end();
             ++i)
        {
            token_ = *i;
            if (token_.size() == 1 &&
                strchr("MmLlHhVvCcSsQqTtAaZz", token_[0]) != 0)
            {
                if (command_) {
                    parseCommand(result);
                }
                command_ = token_[0];
                args_.clear();
            } else {
                args_.push_back(atof(token_.c_str()));
            }
        }
        if (command_) {
            parseCommand(result);
        }
        return result;
    }

    void SvgPathParser::parseCommand(Polygon2 &polygon)
    {
        switch (command_) {
        case 'M':
            parseAbsoluteMovetoCommand(polygon);
            break;

        case 'm':
            parseRelativeMovetoCommand(polygon);
            break;

        case 'L':
            parseAbsoluteLinetoCommand(polygon);
            break;

        case 'l':
            parseRelativeLinetoCommand(polygon);
            break;

        case 'Z':
        case 'z':
            break;

        default:
            throw std::runtime_error(StringBuffer() << "Invalid SVG path command \"" << command_ << "\".");
        }
    }

    void SvgPathParser::parseAbsoluteMovetoCommand(Polygon2 &polygon)
    {
        if (args_.empty() || args_.size() % 2 != 0) {
            throw std::runtime_error(StringBuffer() << "Invalid argument count for SVG path command \"" << command_ << "\".");            
        }
        for (std::size_t i = 0; i + 1 < args_.size(); i += 2) {
            Vector2 vertex(args_[i], args_[i + 1]);
            polygon.vertices.push_back(vertex);
        }
    }

    void SvgPathParser::parseRelativeMovetoCommand(Polygon2 &polygon)
    {
        if (args_.empty() || args_.size() % 2 != 0) {
            throw std::runtime_error(StringBuffer() << "Invalid argument count for SVG path command \"" << command_ << "\".");            
        }
        for (std::size_t i = 0; i + 1 < args_.size(); i += 2) {
            Vector2 vertex(args_[i], args_[i + 1]);
            if (!polygon.vertices.empty()) {
                vertex += polygon.vertices.back();
            }
            polygon.vertices.push_back(vertex);
        }
    }

    void SvgPathParser::parseAbsoluteLinetoCommand(Polygon2 &polygon)
    {
        if (args_.empty() || args_.size() % 2 != 0) {
            throw std::runtime_error(StringBuffer() << "Invalid argument count for SVG path command \"" << command_ << "\".");            
        }
        for (std::size_t i = 0; i + 1 < args_.size(); i += 2) {
            Vector2 vertex(args_[i], args_[i + 1]);
            polygon.vertices.push_back(vertex);
        }
    }

    void SvgPathParser::parseRelativeLinetoCommand(Polygon2 &polygon)
    {
        if (args_.empty() || args_.size() % 2 != 0) {
            throw std::runtime_error(StringBuffer() << "Invalid argument count for SVG path command \"" << command_ << "\".");            
        }
        for (std::size_t i = 0; i + 1 < args_.size(); i += 2) {
            Vector2 vertex(args_[i], args_[i + 1]);
            if (!polygon.vertices.empty()) {
                vertex += polygon.vertices.back();
            }
            polygon.vertices.push_back(vertex);
        }
    }
}
