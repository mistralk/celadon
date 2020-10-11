#ifndef SPECULAR_HPP
#define SPECULAR_HPP

#include "core/BSDF.hpp"

namespace celadon {
    class Specular final : public BSDF {
    public:
        Specular(Color3f reflectance);
        ~Specular();
        
        std::pair<Vec3f, Color3f> sample(std::shared_ptr<Sampler> sampler, const SurfaceHit& hit);

    private:
    };
}

#endif // !SPECULAR_HPP