#ifndef WHITTED_INTEGRATOR_HPP
#define WHITTED_INTEGRATOR_HPP

#include "core/Integrator.hpp"

namespace celadon {
    class WhittedIntegrator final : public Integrator {
    public:
        WhittedIntegrator(std::shared_ptr<Sampler> sampler);
        ~WhittedIntegrator();
        
        Color3f Li(std::shared_ptr<Scene> scene, const Ray& ray) override;

        Color3f scatter(std::shared_ptr<Scene> scene, const Ray& ray, int scattering_depth);

    private:
    };
}

#endif // !WHITTED_INTEGRATOR_HPP