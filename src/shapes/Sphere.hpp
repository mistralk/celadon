#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "core/Shape.hpp"

namespace celadon {
    class BSDF;
    
    class Sphere : public Shape {
    public:
        Sphere(Point3f origin, FLOAT radius, std::shared_ptr<BSDF> bsdf);
        ~Sphere();
        std::optional<SurfaceHit> intersect(const Ray& ray) const final;
    
    private:
        FLOAT m_radius;
    };
}

#endif // !SPHERE_HPP