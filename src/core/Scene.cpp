#include "core/Scene.hpp"
#include "core/Camera.hpp"
#include "core/Shape.hpp"
#include "core/Integrator.hpp"

namespace celadon {

    Scene::Scene() {

    }
    
    Scene::Scene(std::shared_ptr<Camera> camera, std::shared_ptr<Integrator> integrator, std::vector<std::shared_ptr<Shape>> shapes) 
     : m_camera(camera), m_integrator(integrator), m_shapes(shapes) {

    }

    Scene::~Scene() {

    }

    std::optional<SurfaceHit> Scene::intersect(const Ray& ray) const {
        for (const auto& shape : m_shapes) {
            auto hit = shape->intersect(ray);
            if (hit)
                return hit;
        }

        return std::nullopt;
    }

}