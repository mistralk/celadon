#ifndef PATH_INTEGRATOR_HPP
#define PATH_INTEGRATOR_HPP 

#include "core/Integrator.hpp"

namespace celadon {
    class PathIntegrator final : public Integrator {
    public:
        PathIntegrator(std::shared_ptr<Sampler> sampler);
        ~PathIntegrator();
        
        Color3f Li(std::shared_ptr<Scene> scene, const Ray& ray) override;

    private:
    };
}

#endif // !PATH_INTEGRATOR_HPP