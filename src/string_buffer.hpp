#ifndef MONOMI_STRING_BUFFER_HPP
#define MONOMI_STRING_BUFFER_HPP

#include <sstream>

namespace monomi {
    class StringBuffer {
    public:
        explicit StringBuffer(std::string const &str = std::string());

        template <typename T>
        StringBuffer &operator<<(T const &value)
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
    
    class CStringBuffer {
    public:
        explicit CStringBuffer(std::string const &str = std::string());

        template <typename T>
        CStringBuffer &operator<<(T const &value)
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

#endif // MONOMI_STRING_BUFFER_HPP
