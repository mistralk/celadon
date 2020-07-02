#include "integrators/NormalIntegrator.hpp"

#include "core/Ray.hpp"
#include "core/Scene.hpp"

namespace celadon {
    NormalIntegrator::NormalIntegrator() {

    }

    NormalIntegrator::~NormalIntegrator() {

    }

    Color3f NormalIntegrator::Li(std::shared_ptr<Scene> scene, const Ray& ray) {
        Color3f Li(0, 0, 0);
        
        auto hit = scene->intersect(ray);

        if (hit) {
            Li.x = hit->n.x + 1;
            Li.y = hit->n.y + 1;
            // Multiplying n.z by -1 is just to make it visually identical to the right-handed example
            // because our renderer uses left-handed coordinate sytstem.
            Li.z = -hit->n.z + 1; 
            Li *= 0.5;
        }
        else
            Li = background_color(ray.dir);
        
        return Li;
    }
}