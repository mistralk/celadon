#include "shapes/Triangle.hpp"
#include "core/Ray.hpp"
#include "core/BSDF.hpp"

namespace celadon {

    Triangle::Triangle(Point3f v0, Point3f v1, Point3f v2, Normal3f normal, std::shared_ptr<BSDF> bsdf) 
     : Shape(v0, bsdf), m_vertices{v0, v1, v2}, m_normal(normal) {

    }

    Triangle::~Triangle() {

    }

    std::optional<SurfaceHit> Triangle::intersect(const Ray& ray) const {
        // Solve the linear system
        const Vec3f E1 = m_vertices[1] - m_vertices[0];
        const Vec3f E2 = m_vertices[2] - m_vertices[0];
        const Vec3f T = ray.o - m_vertices[0];
        const Vec3f& D = ray.dir;
        const Vec3f P = D.cross(E2);
        const Vec3f Q = T.cross(E1);

        if (P.dot(E1) > -K_EPSILON && P.dot(E1) < K_EPSILON)
           return std::nullopt;

        const Vec3f tuv = 1.0 / P.dot(E1) * Vec3f(Q.dot(E2), P.dot(T), Q.dot(D));
        const auto& t = tuv.x; // distance from ray origin to intersection point
        const auto& u = tuv.y;
        const auto& v = tuv.z;
        
        // Test invariants
        if (u < 0.0 || u > 1.0 || v < 0.0 || u+v > 1.0)
            return std::nullopt;

        //if (u >= 0 && v >= 0) {
        if (t > K_EPSILON) {
            return SurfaceHit{ray.o + t*D, m_normal, -D.normalize(), m_bsdf, t};
        }
        else {
            return std::nullopt;
        }
    }
}