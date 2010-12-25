#ifndef MONOMI_TYPE_HPP
#define MONOMI_TYPE_HPP

#include <iostream>
#include <typeinfo>

namespace monomi {
    // Wrapper for std::type_info with value semantics and a richer comparison
    // interface.
    class Type {
    public:
        explicit Type(std::type_info const &info = typeid(void));

        std::type_info const &info() const;

    private:
        std::type_info const *info_;
    };

    bool operator==(Type const &left, Type const &right);
    bool operator!=(Type const &left, Type const &right);

    bool operator<(Type const &left, Type const &right);
    bool operator<=(Type const &left, Type const &right);
    bool operator>=(Type const &left, Type const &right);
    bool operator>(Type const &left, Type const &right);

    // Outputs the demangled, namespace-qualified type name.
    std::ostream &operator<<(std::ostream &out, Type const &type);
}

#endif // MONOMI_TYPE_HPP
