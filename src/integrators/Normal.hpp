#ifndef NORMAL_INTEGRATOR_HPP
#define NORMAL_INTEGRATOR_HPP

#include "core/Integrator.hpp"

namespace celadon {
    class NormalIntegrator final : public Integrator {
    public:
        NormalIntegrator(std::shared_ptr<Sampler> sampler);
        ~NormalIntegrator();

        Color3f Li(std::shared_ptr<Scene> scene, const Ray& ray) override;

    private:
    };
}

#endif // !NORMAL_INTEGRATOR_HPP