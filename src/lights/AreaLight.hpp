#ifndef AREA_LIGHT_HPP 
#define AREA_LIGHT_HPP 

#include <memory>

#include "core/Light.hpp"

namespace celadon {

    class Shape;
    class AreaLight final : public Light {
    public:
        AreaLight(Color3f radiance, std::shared_ptr<Shape> shape);
        ~AreaLight();

        std::pair <Vec3f, Color3f> sample(const Point2f& u, std::shared_ptr<Scene> scene, const SurfaceHit& hit);
        FLOAT pdf();

    private:
        std::shared_ptr<Shape> m_shape;

    };
}

#endif // !AREA_LIGHT_HPP