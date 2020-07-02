#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <optional>

#include "core/Math.hpp"
#include "core/SurfaceHit.hpp"

namespace celadon {
    struct Ray;

    class Shape {
    public:
        Shape(Point3f origin) : m_origin(origin) {};
        virtual ~Shape() = default;

        virtual std::optional<SurfaceHit> intersect(const Ray& ray) const = 0;

    protected:
        Point3f m_origin;

    };
}

#endif // !SHAPE_HPP