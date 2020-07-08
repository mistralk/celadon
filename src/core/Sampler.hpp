#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include "core/Math.hpp"

#include <memory>

namespace celadon {
    class Sampler {
    public:
        Sampler(uint64_t samples_per_pixel)
        : m_samples_per_pixel(samples_per_pixel) { }

        virtual ~Sampler() = default;

        virtual std::shared_ptr<Sampler> clone() = 0;

        virtual FLOAT get_1d() = 0;
        virtual Point2f get_2d() = 0;

    protected:
        const uint64_t m_samples_per_pixel;
    };
}

#endif // !SAMPLER_HPP