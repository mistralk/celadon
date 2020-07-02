#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>

#include "core/Math.hpp"

namespace celadon {
    class Image {
    public:
        Image(size_t width, size_t height);
        ~Image();

        void set_pixel(const Point2f& pixel, const Color3f& color);
        void set_bitmap();
        std::pair<size_t, size_t> get_width_height() const;
        unsigned char* get_bitmap_array() const;

    private:
        std::vector<Color3f> m_framebuffer;
        unsigned char* m_bitmap;
        size_t m_width;
        size_t m_height;
    };
}

#endif // !IMAGE_HPP