#include "core/Scene.hpp"
#include "core/Camera.hpp"
#include "core/Shape.hpp"
#include "core/Integrator.hpp"

namespace celadon {

    Scene::Scene() {

    }
    
    Scene::Scene(std::shared_ptr<Camera> camera,
            std::shared_ptr<Integrator> integrator, 
            std::vector<std::shared_ptr<Shape>> shapes,
            std::vector<std::shared_ptr<Light>> lights)
     : m_camera(camera), m_integrator(integrator), m_shapes(shapes), m_lights(lights) {

    }

    Scene::~Scene() {

    }
    
    std::optional<SurfaceHit> Scene::intersect(const Ray& ray) const {
        SurfaceHit hit;
        hit.distance = 123456789.0;
        bool is_hit = false;

        for (const auto& shape : m_shapes) {
            auto temp_hit = shape->intersect(ray);
            if (temp_hit) {
                is_hit = true;
                if (temp_hit->distance <= hit.distance)
                    hit = temp_hit.value();
            }
        }

        if (is_hit)
            return hit;
        else
            return std::nullopt;
    }

    bool Scene::test_occlusion(const Ray& ray, std::shared_ptr<Shape> me) const {
        for (const auto& shape : m_shapes) {
            if (shape == me) continue;
            
            auto hit = shape->intersect(ray);
            if (hit)
                return true;
        }
        
        return false;
    }

}