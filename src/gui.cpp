#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <GLFW/glfw3.h>

#include "core/Renderer.hpp"
#include "core/Scene.hpp"
#include "core/Image.hpp"
#include "core/Math.hpp"
#include "core/Timer.hpp"

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

using namespace celadon;

size_t width = 600, height = 400;

std::shared_ptr<celadon::Scene> make_test_scene() {
    //auto camera = std::make_shared<PinholeCamera>(Point3f(0, 2, 1), Point3f(0, 0, 1), Vec3f(-1, 0, 0), 60, (FLOAT)width/(FLOAT)height);
    auto camera = std::make_shared<PinholeCamera>(Point3f(0, 1, -2), Point3f(0, 0, 1), Vec3f(0, 1, 0), 60, (FLOAT)width/(FLOAT)height);
    auto sampler = std::make_shared<RandomSampler>(1);
    auto integrator = std::make_shared<PathIntegrator>(sampler);    
    //auto integrator = std::make_shared<NormalIntegrator>(sampler);
    std::vector<std::shared_ptr<Shape>> shapes;
    std::vector<std::shared_ptr<Light>> lights;

    auto lambertian_red= std::make_shared<Lambertian>(Color3f(0.5, 0.3, 0.3));
    auto lambertian_green= std::make_shared<Lambertian>(Color3f(0.3, 0.5, 0.3));
    auto lambertian_blue = std::make_shared<Lambertian>(Color3f(0.3, 0.3, 0.5));
    auto lambertian_white = std::make_shared<Lambertian>(Color3f(0.9, 0.9, 0.9));
    auto mirror = std::make_shared<Specular>(Color3f(1.0, 1.0, 1.0));

    shapes.push_back(std::make_shared<Sphere>(Point3f(-0.8, 0, 0.4), 0.5, lambertian_white));
    shapes.push_back(std::make_shared<Sphere>(Point3f(0, 0, 1), 0.5, mirror));
    shapes.push_back(std::make_shared<Sphere>(Point3f(1.0, 0, 1.6), 0.5, lambertian_red));
    shapes.push_back(std::make_shared<Sphere>(Point3f(0.5, 0, -1.6), 0.5, lambertian_green));
    shapes.push_back(std::make_shared<Sphere>(Point3f(0, -100.5, 1), 100, lambertian_white));
    
    Point3f vertices[3] = {
        Point3f(-0.5, 1.3, 0.5),
        Point3f(-0.8, 0.8, 0.3),
        Point3f(-0.2, 0.9, 0.6)};

    auto e1 = vertices[1] - vertices[0];
    auto e2 = vertices[2] - vertices[0];
    auto n = e2.cross(e1).normalize();
    shapes.push_back(std::make_shared<Triangle>(vertices, n, lambertian_blue));
    
    Point3f vertices1[3] = {
        Point3f(0, 0.5, 1.0),
        Point3f(-1, 0.5, -1),
        Point3f(1, 0.5, -1)};

    auto e11 = vertices1[1] - vertices1[0];
    auto e22 = vertices1[2] - vertices1[0];
    auto n1 = e22.cross(e11).normalize();
    //shapes.push_back(std::make_shared<Triangle>(vertices1, n1, lambertian_red));
    
    //lights.push_back(std::make_shared<PointLight>(Color3f(1, 1, 1), Point3f(0, 1, 0)));
    
    
    auto light_ball0 = std::make_shared<Sphere>(Point3f(0.0, 1.1, 0.3), 0.3);
    auto light_ball1 = std::make_shared<Sphere>(Point3f(-0.5, 1.1, 0.3), 0.3);
    auto light_ball2 = std::make_shared<Sphere>(Point3f(0.5, 1.1, 0.3), 0.3);
    shapes.push_back(light_ball0);
    //shapes.push_back(light_ball1);
    //shapes.push_back(light_ball2);
    lights.push_back(std::make_shared<AreaLight>(Color3f(1.0, 1.0, 1.0), std::shared_ptr<Sphere>(light_ball0)));
    //lights.push_back(std::make_shared<AreaLight>(Color3f(0.0, 1.0, 0.0), std::shared_ptr<Sphere>(light_ball1)));
    //lights.push_back(std::make_shared<AreaLight>(Color3f(0.0, 0.0, 1.0), std::shared_ptr<Sphere>(light_ball2)));

    return std::make_shared<Scene>(camera, integrator, shapes, lights);
}

int main() {
    auto image = std::make_shared<celadon::Image>(width, height);
    
    celadon::Renderer renderer(image);
    auto scene = make_test_scene();

    // scene->test_description();

    renderer.setup();
    // renderer.render(scene); 

    
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(width, height, "Celadon", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glOrtho(0, 1, 1, 0, -1, 1);

    // Create one OpenGL texture
    GLuint texture_id;
    glGenTextures(1, &texture_id);

    // "Bind" the newly created texture : all future texturlibrary machine type 'x64' conflicts with target machine type 'x86'e functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glEnable(GL_TEXTURE_2D);

    Timer timer;
    unsigned long long int iteration = 0;
    double accumulated_time = 0.f;
    
    while (!glfwWindowShouldClose(window)) {

        timer.start();
        //--------------------------------
        renderer.run_one_iteration(scene);
        //--------------------------------
        iteration++;
        timer.end();
        accumulated_time += timer.elapsed();

        unsigned char* bitmap = image->get_bitmap_array();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Give the image to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 0.0); // left-top
        glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 1.0); // left-bottom
        glTexCoord2f(1.0, 0.0); glVertex2f(1.0, 1.0); // right-bottom
        glTexCoord2f(1.0, 1.0); glVertex2f(1.0, 0.0); // right-top
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        char title[256];
        sprintf(title, "%lld samples/pixel", image->get_spp());
        glfwSetWindowTitle(window, title);

        /* Poll for and process events */
        glfwPollEvents();
    }

    auto average_iteration_time = accumulated_time / iteration;
    std::cout << "Number of iterations: " << iteration << std::endl;
    std::cout << "Average iteration time: " << average_iteration_time << " seconds" << std::endl;
    // std::cout << "Samples per pixel: " << image->get_spp() << std::endl;

    glfwTerminate();

    return 0;
}