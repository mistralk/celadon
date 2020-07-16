#include "integrators/Normal.hpp"

#include "core/Ray.hpp"
#include "core/Scene.hpp"

namespace celadon {
    NormalIntegrator::NormalIntegrator() 
     : Integrator(nullptr) {

    }

    NormalIntegrator::~NormalIntegrator() {

    }

    Color3f NormalIntegrator::Li(std::shared_ptr<Scene> scene, const Ray& ray) {
        Color3f Lo(0, 0, 0);
        
        auto hit = scene->intersect(ray);

        if (hit) {
            Lo.x = hit->n.x + 1;
            Lo.y = hit->n.y + 1;
            // Multiplying n.z by -1 is just to make it visually identical to the right-handed example
            // because our renderer uses left-handed coordinate sytstem.
            Lo.z = -hit->n.z + 1; 
            Lo *= 0.5;
        }
        else
            Lo = background_color(ray.dir);
        
        return Lo;
    }
}