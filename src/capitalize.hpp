#ifndef MONOMI_CAPITALIZE_HPP
#define MONOMI_CAPITALIZE_HPP

#include <sstream>
#include <string>

namespace monomi {
    std::string capitalize(std::string const &str);

    template <typename T>
    std::string capitalize(T const &value)
    {
        std::ostringstream out;
        out << value;
        std::string result = out.str();
        if (!result.empty() && 'a' <= result[0] && result[0] <= 'z') {
            result[0] += 'A' - 'a';
        }
        return result;
    }
}

#endif // MONOMI_CAPITALIZE_HPP
