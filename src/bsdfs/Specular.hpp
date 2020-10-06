#ifndef SPECULAR_HPP
#define SPECULAR_HPP

#include "core/BSDF.hpp"

namespace celadon {
    class Specular final : public BSDF {
    public:
        Specular(Color3f reflectance);
        ~Specular();
        
        Vec3f sample_direction(std::shared_ptr<Sampler> sampler, const SurfaceHit& hit);

    private:
    };
}

#endif // !SPECULAR_HPP