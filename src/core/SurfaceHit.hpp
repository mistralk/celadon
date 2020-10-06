#ifndef SURFACE_HIT_HPP
#define SURFACE_HIT_HPP

#include "core/Math.hpp"

namespace celadon {
    class BSDF;
    
    struct SurfaceHit {
        Point3f p;
        Normal3f n;
        Vec3f wo;
        std::shared_ptr<BSDF> bsdf;

        FLOAT distance;
    };
}

#endif // !SURFACE_HIT_HPP