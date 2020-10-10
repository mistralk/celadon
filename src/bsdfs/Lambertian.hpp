#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "core/BSDF.hpp"

namespace celadon {

    class Lambertian final : public BSDF {
    public:
        Lambertian(Color3f reflectance);
        ~Lambertian();
        
        Vec3f sample_direction(std::shared_ptr<Sampler> sampler, const SurfaceHit& hit);
        Color3f reflectance();

    private:
    };
}

#endif // !LAMBERTIAN_HPP