#ifndef MONOMI_ACTOR_HPP
#define MONOMI_ACTOR_HPP

#include "actor_fwd.hpp"

#include "process.hpp"

namespace monomi {
    class Actor :
        public Process
    {
    public:
        virtual ~Actor()
        { }
    };
}

#endif // MONOMI_ACTOR_HPP
