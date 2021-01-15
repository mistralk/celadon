#ifndef SURFACE_HIT_HPP
#define SURFACE_HIT_HPP

#include <memory>

#include "core/Math.hpp"

namespace celadon {
    class BSDF;
    class Light;
    
    struct SurfaceHit {
        Point3f p;
        Normal3f n;
        Vec3f wo;
        std::shared_ptr<BSDF> bsdf;
        std::shared_ptr<Light> light;

        FLOAT distance;
    };
}

#endif // !SURFACE_HIT_HPP