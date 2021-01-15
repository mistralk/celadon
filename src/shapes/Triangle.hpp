#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "core/Shape.hpp"

namespace celadon {
    class BSDF;
    class Light;

    class Triangle final : public Shape {
    public:
        Triangle(Point3f vertices[3], Normal3f normal, std::shared_ptr<BSDF> bsdf = nullptr);
        ~Triangle();
        std::optional<SurfaceHit> intersect(const Ray& ray) const final;
        Point3f sample_surface(const Point2f& u) const final;
        FLOAT pdf() const;

    private:
        Point3f m_vertices[3];
        Normal3f m_normal;
    };
}

#endif // !TRIANGLE_HPP