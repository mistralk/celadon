#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>

namespace celadon {
    class Scene;
    class Image;
    class Sampler;

    class Renderer {
    public:
        Renderer(std::shared_ptr<Image> image);
        ~Renderer();

        void setup();
        bool render(std::shared_ptr<Scene> scene);
        void run_one_iteration(std::shared_ptr<Scene> scene);

    private:
        std::shared_ptr<Image> m_image;
        std::unique_ptr<Sampler> m_pixel_sampler;
    };
}

#endif // !RENDER_HPP