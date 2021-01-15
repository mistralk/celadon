#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "core/Math.hpp"
#include "core/SurfaceHit.hpp"
#include "lights/AreaLight.hpp"

#include <optional>
#include <memory>
#include <cassert>

namespace celadon {
    struct Ray;
    class BSDF;
    class Light;

    class Shape : public std::enable_shared_from_this<Shape> {
    public:
        Shape(Point3f origin, std::shared_ptr<BSDF> bsdf)
         : m_origin(origin), m_bsdf(bsdf), m_light(nullptr), m_area(0) { };
        virtual ~Shape() = default;

        virtual std::optional<SurfaceHit> intersect(const Ray& ray) const = 0;
        virtual Point3f sample_surface(const Point2f& u) const = 0;
        virtual FLOAT pdf() const = 0;

        std::shared_ptr<BSDF> bsdf() const {
            return m_bsdf;
        }

        std::shared_ptr<AreaLight> area_light() const {
            return m_light;
        }
        
        std::shared_ptr<AreaLight> to_light_source(const Color3f& radiance){
            assert(m_bsdf == nullptr);
            m_light = std::make_shared<AreaLight>(radiance, this->shared_from_this());
            return m_light;
        }

    protected:
        Point3f m_origin;
        FLOAT m_area;

        std::shared_ptr<BSDF> m_bsdf;
        std::shared_ptr<AreaLight> m_light;

    };
}

#endif // !SHAPE_HPP