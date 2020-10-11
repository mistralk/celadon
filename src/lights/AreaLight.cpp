#include "lights/AreaLight.hpp"
#include "core/Shape.hpp"
#include "core/Math.hpp"
#include "core/SurfaceHit.hpp"
#include "core/Ray.hpp"
#include "core/Scene.hpp"

namespace celadon {
    AreaLight::AreaLight(Color3f emittance, std::shared_ptr<Shape> shape)
     : Light(emittance), m_shape(shape) {
         m_shape->set_emittance(m_emittance);
    }

    AreaLight::~AreaLight() {

    }

    Color3f AreaLight::sample(const Point2f& u, std::shared_ptr<Scene> scene, const SurfaceHit& hit) {
        const Point3f& sample_on_shape = m_shape->sample_surface(u);
        const Vec3f& wi = (hit.p - sample_on_shape).normalize();

        const Ray shadow_ray(hit.p + hit.n * K_EPSILON, -wi);
        const auto occluded = scene->test_occlusion(shadow_ray, m_shape);
        if (occluded) {
            return Color3f(0, 0, 0);
        }

        return L(hit, -wi) * abs(hit.n.dot(wi));
    }

    Color3f AreaLight::L(const SurfaceHit& hit, const Vec3f& wo) {
        return m_emittance;
        //if (hit.n.dot(wo) > 0.f) {
        //    return m_emittance;
        //}
        //else return Color3f(0, 0, 0);
    }

    FLOAT AreaLight::pdf() {
        return m_shape->pdf();
    }
}