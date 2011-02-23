#include "capitalize.hpp"

namespace monomi {
    std::string capitalize(std::string const &str)
    {
        std::string result = str;
        if (!result.empty() && 'a' <= result[0] && result[0] <= 'z') {
            result[0] += 'A' - 'a';
        }
        return result;
    }
}
