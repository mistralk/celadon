#ifndef BSDF_HPP
#define BSDF_HPP

#include "core/Math.hpp"
#include "core/SurfaceHit.hpp"

namespace celadon {
    class Sampler;

    class BSDF {
    public:
        BSDF(Color3f reflectance)
         : m_reflectance(reflectance) { }
        virtual ~BSDF() = default;

        virtual Vec3f sample_direction(std::shared_ptr<Sampler> sampler, const SurfaceHit& hit) = 0;

        virtual Color3f reflectance() {
            return m_reflectance;
        }

    protected:
        Color3f m_reflectance;
    };
}

#endif // !BSDF_HPP