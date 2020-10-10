#ifndef AREA_LIGHT_HPP 
#define AREA_LIGHT_HPP 

#include <memory>

#include "core/Light.hpp"

namespace celadon {

    class Shape;
    class AreaLight final : public Light {
    public:
        AreaLight(Color3f emittance, std::shared_ptr<Shape> shape);
        ~AreaLight();

        Color3f sample(const Point2f& u, std::shared_ptr<Scene> scene, const SurfaceHit& hit);
        Color3f L(const SurfaceHit& sampled_point, const Vec3f& wo);
        FLOAT pdf();

    private:
        std::shared_ptr<Shape> m_shape;

    };
}

#endif // !AREA_LIGHT_HPP