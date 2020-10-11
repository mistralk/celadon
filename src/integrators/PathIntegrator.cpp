#include "integrators/PathIntegrator.hpp"
#include "core/Scene.hpp"
#include "core/Ray.hpp"
#include "core/Light.hpp"
#include "core/BSDF.hpp"
#include "samplers/RandomSampler.hpp"

namespace celadon {
    PathIntegrator::PathIntegrator(std::shared_ptr<Sampler> sampler) 
     : Integrator(sampler) {

    }

    PathIntegrator::~PathIntegrator() {

    }

    Color3f PathIntegrator::Li(std::shared_ptr<Scene> scene, const Ray& ray) {
        const int max_depth = 4;
        Color3f pixel(0, 0, 0);
        Color3f throughput(1, 1, 1);

        // Camera ray
        auto path_vertex = scene->intersect(ray);
        if (!path_vertex) // no interction with scene
            return pixel;

        for (int depth = 1 ;; ++depth) {
            // hit an emitter?
            if (path_vertex->bsdf == nullptr) {
                pixel += path_vertex->emittance * throughput;
                break;
            }

            if (depth >= max_depth)
                break;

            const auto [wo, bsdf_reflectance] = path_vertex->bsdf->sample(m_sampler, *path_vertex);

            // direct
            if (path_vertex->bsdf->is_specular == false) {
                for (const auto& light : scene->lights()) {
                    pixel += light->sample(m_sampler->get_2d(), scene, *path_vertex) * bsdf_reflectance * throughput;
                }
            }

            // indirect
            throughput *= bsdf_reflectance;
            const auto next_vertex = path_vertex->p + K_EPSILON * path_vertex->n;
            const auto scattered_ray = Ray(next_vertex, wo);
            path_vertex = scene->intersect(scattered_ray);
        }

        RGB_clamp(pixel);
        return pixel;

        //return scatter(scene, ray, 4);
    }
}