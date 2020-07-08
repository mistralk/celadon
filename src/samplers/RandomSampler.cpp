#include "samplers/RandomSampler.hpp"

namespace celadon {

    RandomSampler::RandomSampler(uint64_t samples_per_pixel) 
     : Sampler(samples_per_pixel) {

    }

    RandomSampler::~RandomSampler() {

    }

    std::shared_ptr<Sampler> RandomSampler::clone() {
        /*
         TODO: some copy process
        */
        return std::make_shared<RandomSampler>(m_samples_per_pixel);
    }

    FLOAT RandomSampler::get_1d() {
        return m_rng.rand();
    }
    
    Point2f RandomSampler::get_2d() {
        return Point2f(m_rng.rand(), m_rng.rand());
    }
}