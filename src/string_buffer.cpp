#include "string_buffer.hpp"

namespace monomi {
    StringBuffer::StringBuffer(std::string const &str) :
        out_(str),
        dirty_(true)
    { }

    StringBuffer::operator std::string const &() const
    {
        if (dirty_) {
            str_ = out_.str();
            dirty_ = false;
        }
        return str_;
    }

    CStringBuffer::CStringBuffer(std::string const &str) :
        out_(str),
        dirty_(true)
    { }

    CStringBuffer::operator char const *() const
    {
        if (dirty_) {
            str_ = out_.str();
            dirty_ = false;
        }
        return str_.c_str();
    }
}
