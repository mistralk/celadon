#include "lights/PointLight.hpp"
#include "core/Ray.hpp"
#include "core/Scene.hpp"

#include <utility>

namespace celadon {
        
    PointLight::PointLight(Color3f intensity, Point3f position)
     : Light(intensity), m_position(position) {

     }

    PointLight::~PointLight() {
        
    }

    Color3f PointLight::sample_Li(std::shared_ptr<Scene> scene, const SurfaceHit& hit) {
        auto wi_with_length = (hit.p + hit.n * K_EPSILON) - m_position;
        const auto dist = wi_with_length.length();
        const auto wi = wi_with_length.normalize();

        const Ray shadow_ray(hit.p + hit.n * K_EPSILON, -wi);
        const auto occluded = scene->test_occlusion(shadow_ray);
        if (occluded) {
            return Color3f(0, 0, 0);
        }
        else {
            const auto cos_term = abs(wi.dot(hit.n));
            return m_intensity / (dist * dist) * cos_term;
        }
    }
}