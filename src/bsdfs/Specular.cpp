#include "bsdfs/Specular.hpp"

namespace celadon {
    Specular::Specular(Color3f reflectance) 
     : BSDF(reflectance, true) {

    }

    Specular::~Specular() {

    }
    
    Color3f Specular::evaluate(const SurfaceHit& hit, const Vec3f& wo) {
        return 0;
    }

    std::pair<Vec3f, Color3f> Specular::sample(std::shared_ptr<Sampler> sampler, const SurfaceHit& hit) {
        return {-hit.wo + 2 * hit.wo.dot(hit.n) * hit.n, m_reflectance};
    }
}