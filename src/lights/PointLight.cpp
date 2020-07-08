#include "lights/PointLight.hpp"
#include "core/Ray.hpp"
#include "core/Scene.hpp"

namespace celadon {
        
    PointLight::PointLight(Color3f intensity, Point3f position)
     : Light(intensity), m_position(position) {

     }

    PointLight::~PointLight() {
        
    }

    Color3f PointLight::sample_Li(std::shared_ptr<Scene> scene, const SurfaceHit& hit) {
        auto wi = (hit.p + hit.n * K_EPSILON) - m_position;
        auto dist = wi.length();
        wi = wi.normalize();

        Ray shadow_ray(hit.p + hit.n * K_EPSILON, -wi);
        auto occluded = scene->test_occlusion(shadow_ray);
        if (occluded) {
            return Color3f(0, 0, 0);
        }
        else {
            auto cos_term = abs(wi.dot(hit.n));
            return m_intensity / (dist * dist) * cos_term;
        }
    }
}