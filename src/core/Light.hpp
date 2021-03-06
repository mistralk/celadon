#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "core/Math.hpp"
#include "core/SurfaceHit.hpp"

#include <memory>

namespace celadon {
    class Scene;

    class Light {
    public:
        Light(Color3f radiance)
         : m_radiance(radiance) { }
        virtual ~Light() = default;

        const Color3f& radiance() {
            return m_radiance;
        }
        
        virtual std::pair<Vec3f, Color3f> sample(const Point2f& u, std::shared_ptr<Scene> scene, const SurfaceHit& hit) = 0;

    protected:
        Color3f m_radiance;

    };
}

#endif // !LIGHT_HPP