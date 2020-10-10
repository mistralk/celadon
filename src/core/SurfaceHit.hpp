#ifndef SURFACE_HIT_HPP
#define SURFACE_HIT_HPP

#include <memory>

#include "core/Math.hpp"

namespace celadon {
    class BSDF;
    
    struct SurfaceHit {
        Point3f p;
        Normal3f n;
        Vec3f wo;
        std::shared_ptr<BSDF> bsdf;
        Color3f emittance;

        FLOAT distance;
    };
}

#endif // !SURFACE_HIT_HPP