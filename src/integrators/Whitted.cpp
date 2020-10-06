#include "integrators/Whitted.hpp"
#include "core/Scene.hpp"
#include "core/Ray.hpp"
#include "core/Light.hpp"
#include "core/BSDF.hpp"
#include "samplers/RandomSampler.hpp"

namespace celadon {
    WhittedIntegrator::WhittedIntegrator(std::shared_ptr<Sampler> sampler) 
     : Integrator(sampler) {

    }

    WhittedIntegrator::~WhittedIntegrator() {

    }

    Color3f WhittedIntegrator::Li(std::shared_ptr<Scene> scene, const Ray& ray) {
        return scatter(scene, ray, 4);
    }
    
    Color3f WhittedIntegrator::scatter(std::shared_ptr<Scene> scene, const Ray& ray, int scattering_depth = 0) {
        if (scattering_depth < 0)
            return Color3f(0, 0, 0);

        const auto hit = scene->intersect(ray);

        if (hit) {
            Color3f Lo(0, 0, 0);

            // Direct lighting            
            for (const auto& light : scene->lights()) {
                Lo += hit->bsdf->reflectance() * light->sample_Li(scene, *hit); // cosine term is multiplied in light->sample_Li()
            }

            // Indirect lighting            
            Color3f indirect_Lo(0, 0, 0);
            auto wi = hit->bsdf->sample_direction(m_sampler, *hit);
            Ray scattered_ray(hit->p + K_EPSILON * hit->n, wi);
            indirect_Lo += scatter(scene, scattered_ray, scattering_depth - 1) * hit->bsdf->reflectance();
            Lo += indirect_Lo;
            
            RGB_clamp(Lo);

            return Lo;
        }
        else {
            // background radiance
            return Color3f(1, 1, 1);
        }
    }
}