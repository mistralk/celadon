#include "shapes/Sphere.hpp"
#include "core/Ray.hpp"

namespace celadon {
    Sphere::Sphere(Point3f origin, FLOAT radius)
     : Shape(origin), m_radius(radius) {

    }

    Sphere::~Sphere() {

    }

    std::optional<SurfaceHit> Sphere::intersect(const Ray& ray) const {
        Vec3f oc = ray.o - m_origin;
        FLOAT a = ray.dir.dot(ray.dir);
        FLOAT b = 2.0 * oc.dot(ray.dir);
        FLOAT c = oc.dot(oc) - m_radius * m_radius;
        FLOAT discriminant = b * b - 4.0 * a * c;

        if (discriminant > 0.0) {
            SurfaceHit hit;
            FLOAT t0 = (-b - sqrt(discriminant)) / (2.0 * a);
            
            // Temporally, clipping planes zmin = 0.0 and zmax = 123456789.0
            if (0.0 < t0 && t0 < 123456789.0) {
                hit.p = ray.o + t0 * ray.dir;
                hit.n = (hit.p - m_origin) / m_radius;
                hit.distance = (hit.p - ray.o).length();
                return hit;
            }

            FLOAT t1 = (-b + sqrt(discriminant)) / (2.0 * a);
            if (0.0 < t1 && t1 < 123456789.0) {
                hit.p = ray.o + t1 * ray.dir;
                hit.n = (hit.p - m_origin) / m_radius;
                hit.distance = (hit.p - ray.o).length();
                return hit;
            }
        }
        
        return std::nullopt;
    }
}