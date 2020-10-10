#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "core/Math.hpp"
#include "core/SurfaceHit.hpp"

#include <optional>
#include <memory>

namespace celadon {
    struct Ray;
    class BSDF;
    class Light;

    class Shape {
    public:
        Shape(Point3f origin, std::shared_ptr<BSDF> bsdf, std::shared_ptr<Light> emitter)
         : m_origin(origin), m_bsdf(bsdf), m_emittance(Color3f(0,0,0)), m_area(0) { };
        virtual ~Shape() = default;

        virtual std::optional<SurfaceHit> intersect(const Ray& ray) const = 0;
        virtual Point3f sample_surface(const Point2f& u) const = 0;
        virtual FLOAT pdf() const = 0;

        std::shared_ptr<BSDF> bsdf() const {
            return m_bsdf;
        }
        
        Color3f emittance() const {
            return m_emittance;
        }

        void set_emittance(const Color3f& emittance) {
            m_emittance = emittance;
        }

    protected:
        std::shared_ptr<BSDF> m_bsdf;
        Color3f m_emittance;
        Point3f m_origin;
        FLOAT m_area;

    };
}

#endif // !SHAPE_HPP