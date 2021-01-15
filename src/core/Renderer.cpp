#include "core/Renderer.hpp"
#include "core/Scene.hpp"
#include "core/Camera.hpp"
#include "core/Image.hpp"
#include "core/Integrator.hpp"
#include "samplers/RandomSampler.hpp"

namespace celadon {
    Renderer::Renderer(std::shared_ptr<Image> image) 
     : m_image(image), m_pixel_sampler(std::make_unique<RandomSampler>(1)) {

    }

    Renderer::~Renderer() {

    }

    void Renderer::setup() {

    }

    bool Renderer::render(std::shared_ptr<Scene> scene) {
        while (true) {
            run_one_iteration(scene);
        }
    }

    void Renderer::run_one_iteration(std::shared_ptr<Scene> scene) {
        auto camera = scene->camera();
        auto integrator = scene->integrator();
        auto [img_width, img_height] = m_image->get_width_height();

        for (size_t y = 0; y < img_height; ++y) {
            for (size_t x = 0; x < img_width; ++x) {
                Color3f Li(0, 0, 0);

                FLOAT u = ((FLOAT)x + m_pixel_sampler->get_1d()) / (FLOAT)img_width;
                FLOAT v = ((FLOAT)y + m_pixel_sampler->get_1d()) / (FLOAT)img_height;

                auto ray = camera->generate_ray(Point2f(u, v));
                Li += integrator->Li(scene, ray);
                
                //Li = Color3f(sqrt(Li.x), sqrt(Li.y), sqrt(Li.z)); // gamma correction
                m_image->accumulate_pixel(Point2f(x, y), Li);
            }
        }

        m_image->add_spp_count(1);
        m_image->set_bitmap();
    }
}