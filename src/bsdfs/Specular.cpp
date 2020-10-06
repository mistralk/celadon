#include "bsdfs/Specular.hpp"

namespace celadon {
    Specular::Specular(Color3f reflectance) 
     : BSDF(reflectance) {

    }

    Specular::~Specular() {

    }
    
    Vec3f Specular::sample_direction(std::shared_ptr<Sampler> sampler, const SurfaceHit& hit) {
        return -hit.wo + 2 * hit.wo.dot(hit.n) * hit.n;
    }
}