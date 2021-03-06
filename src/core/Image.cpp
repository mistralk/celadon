#include "core/Image.hpp"

namespace celadon {
    Image::Image(size_t width, size_t height) 
     : m_width(width), m_height(height), m_total_spp(0) {
         m_framebuffer.resize(m_width * m_height);
         m_bitmap = new unsigned char[m_width * m_height * 3];
    }

    Image::~Image() {
        delete m_bitmap;
    }

    void Image::set_pixel(const Point2f& pixel, const Color3f& color) {
        m_framebuffer[pixel.y * m_width + pixel.x] = color;
    }
    
    void Image::accumulate_pixel(const Point2f& pixel, const Color3f& color) {
        m_framebuffer[pixel.y * m_width + pixel.x] += color;
    }
    
    void Image::add_spp_count(uint64_t spp) {
        m_total_spp += spp;
    }

    uint64_t Image::get_spp() const {
        return m_total_spp;
    }

    void Image::set_bitmap() {
        for (size_t y = 0; y < m_height; ++y) {
            for (size_t x = 0; x < m_width; ++x) {
                size_t idx = y * 3 * m_width + x * 3;
                m_bitmap[idx + 0] = (unsigned char)(m_framebuffer[y * m_width + x].x / m_total_spp * 255);
                m_bitmap[idx + 1] = (unsigned char)(m_framebuffer[y * m_width + x].y / m_total_spp * 255);
                m_bitmap[idx + 2] = (unsigned char)(m_framebuffer[y * m_width + x].z / m_total_spp * 255);
            }
        }
    }

    std::pair<size_t, size_t> Image::get_width_height() const {
        return std::make_pair(m_width, m_height);
    }

    unsigned char* Image::get_bitmap_array() const {
        return m_bitmap;
    }
}