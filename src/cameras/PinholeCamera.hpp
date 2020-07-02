#ifndef PINHOLE_CAMERA_HPP
#define PINHOLE_CAMERA_HPP

#include "core/Camera.hpp"

namespace celadon {
    class PinholeCamera final : public Camera {
    public:
        PinholeCamera(Point3f position, Point3f lookat, Vec3f up, FLOAT vfov, FLOAT aspect_ratio);
        ~PinholeCamera();

        Ray generate_ray(Point2f pixel) override;
        
    private:
        Point3f m_lower_left_corner;
        Vec3f m_horizontal;
        Vec3f m_vertical;
    };
}

#endif // !PINHOLE_CAMERA_HPP