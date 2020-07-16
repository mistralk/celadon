#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include <memory>

#include "core/Math.hpp"

namespace celadon {
    class Scene;
    class Sampler;
    struct Ray;

    class Integrator {
    public:
        Integrator(std::shared_ptr<Sampler> sampler)
         : m_sampler(sampler) { }
        virtual ~Integrator() = default;

        virtual Color3f Li(std::shared_ptr<Scene> scene, const Ray& ray) = 0;

    protected:
        std::shared_ptr<Sampler> m_sampler;
    };
}

#endif // !INTEGRATOR_HPP