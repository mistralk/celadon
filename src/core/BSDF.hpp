#ifndef BSDF_HPP
#define BSDF_HPP

#include "core/Math.hpp"
#include "core/SurfaceHit.hpp"

namespace celadon {
    class Sampler;

    class BSDF {
    public:
        BSDF(Color3f reflectance, bool specular = false)
         : m_reflectance(reflectance), is_specular(specular) { }
        virtual ~BSDF() = default;

        virtual Color3f evaluate(const SurfaceHit& hit, const Vec3f& wo) = 0;
        virtual std::pair<Vec3f, Color3f> sample(std::shared_ptr<Sampler> sampler, const SurfaceHit& hit) = 0;

        const bool is_specular;

    protected:
        Color3f m_reflectance;
    };
}

#endif // !BSDF_HPP