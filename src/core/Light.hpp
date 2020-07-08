#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "core/Math.hpp"
#include "core/SurfaceHit.hpp"

#include <memory>

namespace celadon {
    class Scene;

    class Light {
    public:
        Light(Color3f intensity)
         : m_intensity(intensity) { }
        virtual ~Light() = default;

        virtual Color3f sample_Li(std::shared_ptr<Scene> scene, const SurfaceHit& hit) = 0;

    protected:
        Color3f m_intensity;

    };
}

#endif // !LIGHT_HPP