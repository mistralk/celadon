#ifndef SURFACE_HIT_HPP
#define SURFACE_HIT_HPP

#include "core/Math.hpp"

namespace celadon {
    struct SurfaceHit {
        Point3f p;
        Vec3f wo;
        Normal3f n;

        FLOAT distance;
    };
}

#endif // !SURFACE_HIT_HPP