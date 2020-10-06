#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "core/Shape.hpp"

namespace celadon {
    class BSDF;

    class Triangle final : public Shape {
    public:
        Triangle(Point3f v0, Point3f v1, Point3f v2, Normal3f normal, std::shared_ptr<BSDF> bsdf);
        ~Triangle();
        std::optional<SurfaceHit> intersect(const Ray& ray) const final;

    private:
        Point3f m_vertices[3];
        Normal3f m_normal;
    };
}

#endif // !TRIANGLE_HPP