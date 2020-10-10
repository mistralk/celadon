#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "core/Shape.hpp"

namespace celadon {
    class BSDF;
    class Light;
    
    class Sphere : public Shape {
    public:
        Sphere(Point3f origin, FLOAT radius, std::shared_ptr<BSDF> bsdf = nullptr, std::shared_ptr<Light> emitter = nullptr);
        ~Sphere();
        std::optional<SurfaceHit> intersect(const Ray& ray) const final;
        Point3f sample_surface(const Point2f& u) const final;
        FLOAT pdf() const;
    
    private:
        FLOAT m_radius;
    };
}

#endif // !SPHERE_HPP