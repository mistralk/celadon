#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>
#include <optional>

#include "core/SurfaceHit.hpp"

#include "cameras/PinholeCamera.hpp"
#include "shapes/Sphere.hpp"
#include "shapes/Triangle.hpp"
#include "integrators/Normal.hpp"
#include "integrators/PathIntegrator.hpp"
#include "lights/PointLight.hpp"
#include "lights/AreaLight.hpp"
#include "bsdfs/Lambertian.hpp"
#include "bsdfs/Specular.hpp"
#include "samplers/RandomSampler.hpp"

namespace celadon {
    class Camera;
    class Shape;
    class Integrator;
    class Light;
    struct Ray;

    class Scene {
    public:
        Scene();
        Scene(std::shared_ptr<Camera> camera,
              std::shared_ptr<Integrator> integrator, 
              std::vector<std::shared_ptr<Shape>> shapes,
              std::vector<std::shared_ptr<Light>> lights);
        ~Scene();

        std::optional<SurfaceHit> intersect(const Ray& ray) const;
        bool test_occlusion(const Ray& ray, std::shared_ptr<Shape> me, const FLOAT ray_to_light_dist) const;

        const std::shared_ptr<Camera> camera() const {
            return m_camera;
        }
        
        const std::shared_ptr<Integrator> integrator() const {
            return m_integrator;
        }
        
        const std::vector<std::shared_ptr<Light>> lights() const {
            return m_lights;
        }

    private:
        std::shared_ptr<Camera> m_camera;
        std::shared_ptr<Integrator> m_integrator;
        std::vector<std::shared_ptr<Shape>> m_shapes;
        std::vector<std::shared_ptr<Light>> m_lights;

    public:
        static std::shared_ptr<celadon::Scene> make_test_scene(int width, int height) {
            //auto camera = std::make_shared<PinholeCamera>(Point3f(0, 2, 1), Point3f(0, 0, 1), Vec3f(-1, 0, 0), 60, (FLOAT)width/(FLOAT)height);
            auto camera = std::make_shared<PinholeCamera>(Point3f(0, 1, -3), Point3f(0, 0, 1), Vec3f(0, 1, 0), 60, (FLOAT)width/(FLOAT)height);
            auto sampler = std::make_shared<RandomSampler>(1);
            auto integrator = std::make_shared<PathIntegrator>(sampler);    
            //auto integrator = std::make_shared<NormalIntegrator>(sampler);
            std::vector<std::shared_ptr<Shape>> shapes;
            std::vector<std::shared_ptr<Light>> lights;

            auto lambertian_red= std::make_shared<Lambertian>(Color3f(0.4, 0.1, 0.1));
            auto lambertian_green= std::make_shared<Lambertian>(Color3f(0.3, 0.5, 0.3));
            auto lambertian_blue = std::make_shared<Lambertian>(Color3f(0.3, 0.3, 0.5));
            auto lambertian_white = std::make_shared<Lambertian>(Color3f(0.5, 0.5, 0.5));
            auto mirror = std::make_shared<Specular>(Color3f(1.0, 1.0, 1.0));

            shapes.push_back(std::make_shared<Sphere>(Point3f(-0.8, 0, 0.4), 0.5, lambertian_white));
            shapes.push_back(std::make_shared<Sphere>(Point3f(0, 0, 1), 0.5, mirror));
            shapes.push_back(std::make_shared<Sphere>(Point3f(1.0, 0, 1.6), 0.5, lambertian_red));
            shapes.push_back(std::make_shared<Sphere>(Point3f(0.5, 0, -1.6), 0.5, mirror));
            //shapes.push_back(std::make_shared<Sphere>(Point3f(0, -101.5, 1), 100, lambertian_white));
            
            Point3f vertices[3] = {
                Point3f(0, -0.5, 100),
                Point3f(-100, -0.5, -50),
                Point3f(100, -0.5, -50)};
            auto e1 = vertices[1] - vertices[0];
            auto e2 = vertices[2] - vertices[0];
            auto n = e2.cross(e1).normalize();
            shapes.push_back(std::make_shared<Triangle>(vertices, n, lambertian_white));
            
            /*
            Point3f vertices1[3] = {
                Point3f(0, 0.5, 1.0),
                Point3f(-1, 0.5, -1),
                Point3f(1, 0.5, -1)};
            auto e11 = vertices1[1] - vertices1[0];
            auto e22 = vertices1[2] - vertices1[0];
            auto n1 = e22.cross(e11).normalize();
            */
            Point3f vertices1[3] = {
                Point3f(-0.5, 1.3, 0.5),
                Point3f(-0.8, 0.8, 0.3),
                Point3f(-0.2, 0.9, 0.6)};
            auto e11 = vertices[1] - vertices[0];
            auto e22 = vertices[2] - vertices[0];
            auto n1 = e2.cross(e1).normalize();
            //shapes.push_back(std::make_shared<Triangle>(vertices1, n1, mirror));
            
            //lights.push_back(std::make_shared<PointLight>(Color3f(0, 0, 1), Point3f(0, 1.2, 0.3)));
            //lights.push_back(std::make_shared<PointLight>(Color3f(1, 0, 0), Point3f(1.5, 2, 0)));
            
            
            auto light_ball0 = std::make_shared<Sphere>(Point3f(0.0, 1.1, 0.3), 0.3);
            shapes.push_back(light_ball0);
            lights.push_back(light_ball0->to_light_source(Color3f(1, 1, 1)));
            /*
            auto light_ball1 = std::make_shared<Sphere>(Point3f(1.0, 1.2, 0.3), 0.003);
            lights.push_back(light_ball1->to_light_source(Color3f(1, 0, 0)));
            auto light_ball2 = std::make_shared<Sphere>(Point3f(-1.0, 1.2, 0.3), 0.003);
            lights.push_back(light_ball2->to_light_source(Color3f(0, 0, 1)));
            */
            return std::make_shared<Scene>(camera, integrator, shapes, lights);
        }
    };
}
#endif // !SCENE_HPP