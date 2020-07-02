#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include <memory>

#include "core/Math.hpp"

namespace celadon {
    class Scene;
    struct Ray;

    class Integrator {
    public:
        Integrator() = default;
        virtual ~Integrator() = default;

        virtual Color3f Li(std::shared_ptr<Scene> scene, const Ray& ray) = 0;

    protected:
    };
}

#endif // !INTEGRATOR_HPP