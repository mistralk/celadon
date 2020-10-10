#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "core/Math.hpp"
#include "core/SurfaceHit.hpp"

#include <memory>

namespace celadon {
    class Scene;

    class Light {
    public:
        Light(Color3f emittance)
         : m_emittance(emittance) { }
        virtual ~Light() = default;

        virtual Color3f sample(const Point2f& u, std::shared_ptr<Scene> scene, const SurfaceHit& hit) = 0;

    protected:
        Color3f m_emittance;

    };
}

#endif // !LIGHT_HPP