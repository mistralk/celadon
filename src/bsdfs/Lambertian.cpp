#include "bsdfs/Lambertian.hpp"
#include "core/Sampler.hpp"

namespace celadon {


    Lambertian::Lambertian(Color3f reflectance = Color3f(0.5, 0.5, 0.5))
     : BSDF(reflectance) {

    }

    Lambertian::~Lambertian() {

    }
    
    Color3f Lambertian::evaluate(const SurfaceHit& hit, const Vec3f& wo) {
        auto weight = m_reflectance * abs(wo.dot(hit.n)) / K_PI;
        return weight;
    }

    std::pair<Vec3f, Color3f> Lambertian::sample(std::shared_ptr<Sampler> sampler, const SurfaceHit& hit) {
        Point3f sphere_p;
        
        // Uniform sampling in an unit sphere via rejection method
        do {
            sphere_p = Point3f(2*sampler->get_1d()-1, 2*sampler->get_1d()-1, 2*sampler->get_1d()-1);
        } while (sphere_p.x * sphere_p.x + sphere_p.y * sphere_p.y + sphere_p.z * sphere_p.z >= 1.0);
        
        auto wo = ((hit.p + hit.n + sphere_p) - hit.p).normalize();
        auto p = 1 / ((4.0/3.0) * K_PI); // p(m) term of MC integration; the volume of a sphere = 4/3 * PI * R^3
        /*
        auto sample = sample_sphere_uniform(sampler->get_2d());
        auto wo = ((hit.p + sample) - hit.p).normalize();
        auto p = 1 / (4 * K_PI);
        */
        auto weight = evaluate(hit, wo) / p;

        return {wo, weight};
    }
}