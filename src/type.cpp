#include "type.hpp"

#ifdef __GNUC__
#include <cxxabi.h>

namespace {
    struct ScopedFree {
        void *ptr;

        ScopedFree(void *ptr = 0) :
            ptr(ptr)
        { }

        ~ScopedFree()
        {
            if (ptr) {
                free(ptr);
            }
        }
    };
}
#endif // __GNUC__

namespace monomi {
    Type::Type(std::type_info const &info) :
        info_(&info)
    { }

    std::type_info const &Type::info() const
    {
        return *info_;
    }

    bool operator==(Type const &left, Type const &right)
    {
        return left.info() == right.info();
    }

    bool operator!=(Type const &left, Type const &right)
    {
        return left.info() != right.info();
    }

    bool operator<(Type const &left, Type const &right)
    {
        return left.info().before(right.info());
    }

    bool operator<=(Type const &left, Type const &right)
    {
        return !(right < left);
    }

    bool operator>=(Type const &left, Type const &right)
    {
        return !(left < right);
    }

    bool operator>(Type const &left, Type const &right)
    {
        return right < left;
    }

    std::ostream &operator<<(std::ostream &out, Type const &type)
    {
#ifdef __GNUC__
        char const *name = type.info().name();
        int status = 0;
        if (char *demangledName = abi::__cxa_demangle(name, 0, 0, &status)) {
            ScopedFree scopedFree(demangledName);
            return out << demangledName;
        } else {
            return out << name;
        }
#else // __GNUC__
        return out << type.info().name();
#endif // __GNUC__
    }
}
