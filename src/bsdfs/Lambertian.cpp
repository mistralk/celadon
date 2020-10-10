#include "bsdfs/Lambertian.hpp"
#include "core/Sampler.hpp"

namespace celadon {


    Lambertian::Lambertian(Color3f reflectance = Color3f(0.5, 0.5, 0.5))
     : BSDF(reflectance) {

    }

    Lambertian::~Lambertian() {

    }
    
    Vec3f Lambertian::sample_direction(std::shared_ptr<Sampler> sampler, const SurfaceHit& hit) {
        Point3f sphere_p;
        do {
            sphere_p = Point3f(2*sampler->get_1d()-1, 2*sampler->get_1d()-1, 2*sampler->get_1d()-1);
        } while (sphere_p.x * sphere_p.x + sphere_p.y * sphere_p.y + sphere_p.z * sphere_p.z >= 1.0);
        
        return (hit.p + hit.n + sphere_p) - hit.p;
    }
    
    Color3f Lambertian::reflectance() {
        return m_reflectance /* * K_INV_PI */;
    }
}