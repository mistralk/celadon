#include "PinholeCamera.hpp"

namespace celadon {
    PinholeCamera::PinholeCamera(Point3f position, Point3f lookat, Vec3f up, FLOAT vfov, FLOAT aspect_ratio) 
     : Camera(position) {
         FLOAT theta = vfov * K_PI / 180.0;
         FLOAT half_height = tan(theta / 2);
         FLOAT half_width = aspect_ratio * half_height;

         Vec3f w = (m_origin - lookat).normalize();
         Vec3f u = up.cross(-w).normalize();
         Vec3f v = w.cross(-u);

         m_lower_left_corner = m_origin - half_width*u - half_height*v - w;
         m_horizontal = 2 * half_width * u;
         m_vertical = 2 * half_height * v;
    }

    PinholeCamera::~PinholeCamera() {

    }

    Ray PinholeCamera::generate_ray(Point2f pixel) {
        // pixel must be normalized
        auto dir = m_lower_left_corner + pixel.x * m_horizontal + pixel.y * m_vertical - m_origin;
        return Ray(m_origin, dir);
    }
}