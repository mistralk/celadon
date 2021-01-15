#include "lights/AreaLight.hpp"
#include "core/Shape.hpp"
#include "core/Math.hpp"
#include "core/SurfaceHit.hpp"
#include "core/Ray.hpp"
#include "core/Scene.hpp"

namespace celadon {
    AreaLight::AreaLight(Color3f radiance, std::shared_ptr<Shape> shape)
     : Light(radiance), m_shape(shape) {
    }

    AreaLight::~AreaLight() {

    }

    std::pair<Vec3f, Color3f> AreaLight::sample(const Point2f& u, std::shared_ptr<Scene> scene, const SurfaceHit& hit) {
        const Point3f& sample_on_shape = m_shape->sample_surface(u);
        Vec3f wo = (sample_on_shape - hit.p);
        const auto dist = (sample_on_shape - hit.p).length();
        wo = wo.normalize();

        const Ray shadow_ray(hit.p + hit.n * K_EPSILON, wo);
        const auto occluded = scene->test_occlusion(shadow_ray, m_shape, dist);
        if (occluded) {
            return {wo, Color3f(0, 0, 0)};
        }

        return {wo, m_radiance * abs(hit.n.dot(wo))};
    }

    FLOAT AreaLight::pdf() {
        return m_shape->pdf();
    }
}