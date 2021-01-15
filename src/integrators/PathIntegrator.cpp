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

    static Color3f background_radiance(const Ray& ray) {
        float t = 0.5 * (ray.dir.normalize().y + 1.0);
        //return Color3f(0.1, 0.1, 0.1);
        return (1.0-t)*Color3f(0.1,0.1,0.1) + (t)*Color3f(0.5, 0.7, 1.0);
    }

    Color3f PathIntegrator::Li(std::shared_ptr<Scene> scene, const Ray& ray) {
        const int max_depth = 4;
        Color3f pixel(0.0, 0.0, 0.0);
        Color3f throughput(1.0, 1.0, 1.0);

        // Cast a camera ray into the scene
        auto path_vertex = scene->intersect(ray);

        /* [Some definitions]
           Path depth = 1: light sources
           Path depth = 2: direct lighting (no scattering)
           Path depth = 3~: indirect lighting (scattering) */
        for (int path_depth = 1 ;; ++path_depth) {

            // No intersection with the scene
            if (!path_vertex) {
                pixel += background_radiance(ray) * throughput;
                break;
            }

            // Path vertex is located on a light source(=an emitter)
            if (path_vertex->light) {
                auto p = 1.0 / ((4.0/3.0) * K_PI);
                // p(m) term of MC integration - we are sampling scattered ray to light sources with Lambertian reflection only
                // and Lambertian is using uniform sphere sampling
                pixel += path_vertex->light->radiance() * throughput / p;
                // TODO: deal with double counting?
                break;
            }
            
            if (path_depth >= max_depth) {
                break;
            }

            // TODO: Next event estimation (stochastically)
            /*
            if (path_vertex->bsdf->is_specular == false) {
                //const auto& light = scene->lights()[(int)(m_sampler->get_1d() + 0.5)];
                for (const auto& light : scene->lights()) {
                    auto [to_light, radiance] = light->sample(m_sampler->get_2d(), scene, *path_vertex);
                    auto bsdf_lighting_weight = path_vertex->bsdf->evaluate(*path_vertex, to_light);
                    pixel += radiance * bsdf_lighting_weight * throughput;
                }
            }*/

            // Compute scattered ray direction `wi` and its BSDF weight F(wi, wo)
            const auto [wi, bsdf_weight] = path_vertex->bsdf->sample(m_sampler, *path_vertex);
            const auto bump_vertex = path_vertex->p + (K_EPSILON * path_vertex->n);
            const auto scattered_ray = Ray(bump_vertex, wi);
            throughput *= bsdf_weight; 
            path_vertex = scene->intersect(scattered_ray);
        }

        RGB_clamp(pixel);
        return pixel;
    }
}