#ifndef RANDOM_SAMPLER_HPP
#define RANDOM_SAMPLER_HPP

#include "core/Sampler.hpp"

namespace celadon {
    class RandomSampler final : public Sampler {
    public:
        RandomSampler(uint64_t samples_per_pixel);
        ~RandomSampler();

        std::shared_ptr<Sampler> clone();

        FLOAT get_1d();
        Point2f get_2d();

    private:
        RNG m_rng;
    };
}

#endif // !RANDOM_SAMPLER_HPP