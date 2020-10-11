#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "core/BSDF.hpp"

namespace celadon {

    class Lambertian final : public BSDF {
    public:
        Lambertian(Color3f reflectance);
        ~Lambertian();
        
        std::pair<Vec3f, Color3f> sample(std::shared_ptr<Sampler> sampler, const SurfaceHit& hit);
        Color3f reflectance(const SurfaceHit& hit);

    private:
    };
}

#endif // !LAMBERTIAN_HPP