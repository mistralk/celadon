#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "core/Light.hpp"

namespace celadon {

    class PointLight final : public Light {
    public:
        PointLight(Color3f emittance, Point3f position);
        ~PointLight();

        Color3f sample(const Point2f& u, std::shared_ptr<Scene> scene, const SurfaceHit& hit);

    private:
        Point3f m_position;

    };
}

#endif // !POINT_LIGHT_HPP