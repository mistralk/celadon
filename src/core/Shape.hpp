#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "core/Math.hpp"
#include "core/SurfaceHit.hpp"

#include <optional>
#include <memory>

namespace celadon {
    struct Ray;
    class BSDF;

    class Shape {
    public:
        Shape(Point3f origin, std::shared_ptr<BSDF> bsdf)
         : m_origin(origin), m_bsdf(bsdf) { };
        virtual ~Shape() = default;

        virtual std::optional<SurfaceHit> intersect(const Ray& ray) const = 0;

        std::shared_ptr<BSDF> bsdf() {
            return m_bsdf;
        }

    protected:
        std::shared_ptr<BSDF> m_bsdf;
        Point3f m_origin;

    };
}

#endif // !SHAPE_HPP