#include "integrators/Whitted.hpp"
#include "core/Scene.hpp"
#include "core/Ray.hpp"
#include "core/Light.hpp"
#include "samplers/RandomSampler.hpp"

namespace celadon {
    WhittedIntegrator::WhittedIntegrator() {

    }

    WhittedIntegrator::~WhittedIntegrator() {

    }

    static Color3f bsdf() {
        Color3f reflectivity(0, 0, 0.7);
        return reflectivity;
    }

    Color3f WhittedIntegrator::Li(std::shared_ptr<Scene> scene, const Ray& ray) {
        auto hit = scene->intersect(ray);
        RandomSampler sampler(1);

        if (hit) {
            Color3f Lo(0, 0, 0);
            // Ambient lighting
            Lo += bsdf() * 0.05;

            // Direct lighting
            for (const auto& light : scene->lights()) {
                Lo += light->sample_Li(scene, *hit);
            }

            // Indirect lighting
            /*
            for (int depth = 0; depth < 0; ++depth) {
                int spp = 32;
                Color3f indirect(0, 0, 0);
                for (int i = 0; i < spp; ++i) {
                    auto wi = sample_hemisphere_cosine(sampler.get_2d());
                    Ray scatter_ray(hit->p + hit->n * K_EPSILON, -wi);
                    hit = scene->intersect(scatter_ray);
                    indirect += point_light_Li(scene, *hit);
                }
                Lo += indirect/spp;
            }
            */
            
            return Lo;
        }
        else {
            // background radiance
            return Color3f(1, 1, 1);
        }
    }
}