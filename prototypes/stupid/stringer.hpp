#ifndef MONOMI_STRINGER_HPP
#define MONOMI_STRINGER_HPP

#include <sstream>

namespace monomi {
    class Stringer {
    public:
        explicit Stringer(std::string const &str = std::string());

        template <typename T>
        Stringer &operator<<(T const &value)
        {
            dirty_ = true;
            out_ << value;
            return *this;
        }

        operator std::string const &() const;

    private:
        std::ostringstream out_;
        mutable std::string str_;
        mutable bool dirty_;
    };
    
    class CStringer {
    public:
        explicit CStringer(std::string const &str = std::string());

        template <typename T>
        CStringer &operator<<(T const &value)
        {
            dirty_ = true;
            out_ << value;
            return *this;
        }

        operator char const *() const;

    private:
        std::ostringstream out_;
        mutable std::string str_;
        mutable bool dirty_;
    };
}

#endif // MONOMI_STRINGER_HPP
