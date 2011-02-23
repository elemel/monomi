#ifndef MONOMI_RANDOM_HPP
#define MONOMI_RANDOM_HPP

#include <boost/random.hpp>

namespace monomi {
    class Random {
    public:
        explicit Random(int seed);

        float generate();

    private:
        typedef boost::mt19937 Engine;
        typedef boost::uniform_real<float> Distribution;
        typedef boost::variate_generator<Engine, Distribution> Generator;

        Generator generator_;
    };
}

#endif // MONOMI_RANDOM_HPP
