#ifndef RAY_HPP
#define RAY_HPP

#include "core/Math.hpp"

namespace celadon {
    struct Ray {
        Point3f o;
        Vec3f dir;

        Ray(const Point3f &origin, const Vec3f &dir)
            : o(origin), dir(dir) { }
    };
}

#endif RAY_HPP // !RAY_HPP