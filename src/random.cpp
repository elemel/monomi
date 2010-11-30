#include "random.hpp"

namespace monomi {
    Random::Random(int seed) :
        generator_(Engine(seed), Distribution(0.0f, 1.0f))
    { }

    float Random::generate()
    {
        return generator_();
    }
}
