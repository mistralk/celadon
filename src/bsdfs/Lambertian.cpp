#include "bsdfs/Lambertian.hpp"
#include "core/Sampler.hpp"

namespace celadon {


    Lambertian::Lambertian(Color3f reflectance = Color3f(0.5, 0.5, 0.5))
     : BSDF(reflectance) {

    }

    Lambertian::~Lambertian() {

    }
    
    std::pair<Vec3f, Color3f> Lambertian::sample(std::shared_ptr<Sampler> sampler, const SurfaceHit& hit) {
        Point3f sphere_p;
        do {
            sphere_p = Point3f(2*sampler->get_1d()-1, 2*sampler->get_1d()-1, 2*sampler->get_1d()-1);
        } while (sphere_p.x * sphere_p.x + sphere_p.y * sphere_p.y + sphere_p.z * sphere_p.z >= 1.0);
        
        const auto wo = (hit.p + hit.n + sphere_p) - hit.p;

        return {wo, reflectance(hit)};
    }
    
    Color3f Lambertian::reflectance(const SurfaceHit& hit) {
        return m_reflectance * K_INV_PI;
    }
}