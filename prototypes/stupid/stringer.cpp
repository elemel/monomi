#include "stringer.hpp"

namespace monomi {
    Stringer::Stringer(std::string const &str) :
        out_(str),
        dirty_(true)
    { }

    Stringer::operator std::string const &() const
    {
        if (dirty_) {
            str_ = out_.str();
            dirty_ = false;
        }
        return str_;
    }

    CStringer::CStringer(std::string const &str) :
        out_(str),
        dirty_(true)
    { }

    CStringer::operator char const *() const
    {
        if (dirty_) {
            str_ = out_.str();
            dirty_ = false;
        }
        return str_.c_str();
    }
}
