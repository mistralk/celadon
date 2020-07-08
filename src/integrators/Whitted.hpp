#ifndef WHITTED_INTEGRATOR_HPP
#define WHITTED_INTEGRATOR_HPP

#include "core/Integrator.hpp"

namespace celadon {
    class WhittedIntegrator final : public Integrator {
    public:
        WhittedIntegrator();
        ~WhittedIntegrator();
        
        Color3f Li(std::shared_ptr<Scene> scene, const Ray& ray) override;

    private:
    };
}

#endif // !WHITTED_INTEGRATOR_HPP