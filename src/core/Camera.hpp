#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "core/Math.hpp"
#include "core/Ray.hpp"

namespace celadon {
    class Camera {
    public:
        Camera(Point3f position) 
         : m_origin(position) { }
        
        virtual ~Camera() = default;

        virtual Ray generate_ray(Point2f pixel) = 0;
    
    protected:
        Point3f m_origin;

    };
}

#endif // !CAMERA_HPP