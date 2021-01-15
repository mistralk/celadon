#include "lights/PointLight.hpp"
#include "core/Ray.hpp"
#include "core/Scene.hpp"

#include <utility>

namespace celadon {
        
    PointLight::PointLight(Color3f emittance, Point3f position)
     : Light(emittance), m_position(position) {

     }

    PointLight::~PointLight() {
        
    }

    std::pair<Vec3f, Color3f> PointLight::sample(const Point2f& u, std::shared_ptr<Scene> scene, const SurfaceHit& hit) {
        auto wo_with_length = m_position - (hit.p + hit.n * K_EPSILON);
        const auto dist = wo_with_length.length();
        const auto wo = wo_with_length.normalize();

        const Ray shadow_ray(hit.p + hit.n * K_EPSILON, wo);
        const auto occluded = scene->test_occlusion(shadow_ray, nullptr, dist);
        if (occluded) {
            return {wo, Color3f(0, 0, 0)};
        }
        else {
            const auto cos_term = abs(wo.dot(hit.n));
            return {wo, m_radiance * cos_term};
        }
    }
}