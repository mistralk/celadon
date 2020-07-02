#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>
#include <optional>
#include "core/SurfaceHit.hpp"

namespace celadon {
    class Camera;
    class Shape;
    class Integrator;
    struct Ray;

    class Scene {
    public:
        Scene();
        Scene(std::shared_ptr<Camera> camera, std::shared_ptr<Integrator> integrator, std::vector<std::shared_ptr<Shape>> shapes);
        ~Scene();

        std::optional<SurfaceHit> intersect(const Ray& ray) const;

        const std::shared_ptr<Camera> camera() const {
            return m_camera;
        }
        
        const std::shared_ptr<Integrator> integrator() const {
            return m_integrator;
        }

    private:
        std::shared_ptr<Camera> m_camera;
        std::shared_ptr<Integrator> m_integrator;
        std::vector<std::shared_ptr<Shape>> m_shapes;

    };
}
#endif // !SCENE_HPP