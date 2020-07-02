#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <GLFW/glfw3.h>

#include "core/Renderer.hpp"
#include "core/Scene.hpp"
#include "core/Image.hpp"
#include "core/Math.hpp"

#include "cameras/PinholeCamera.hpp"
#include "shapes/Sphere.hpp"
#include "integrators/NormalIntegrator.hpp"

using namespace celadon;

size_t width = 200, height = 100;

std::shared_ptr<celadon::Scene> make_test_scene() {
    auto camera = std::make_shared<PinholeCamera>(Point3f(0, 1, 0), Point3f(0, 0, 1), Vec3f(0, 1, 0), 90, (FLOAT)width/(FLOAT)height);
    auto integrator = std::make_shared<NormalIntegrator>();
    
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Sphere>(Point3f(0, 0, 1), 0.5));
    shapes.push_back(std::make_shared<Sphere>(Point3f(1.0, 0, 1.6), 0.5));
    shapes.push_back(std::make_shared<Sphere>(Point3f(0, -100.5, 1), 100));

    return std::make_shared<Scene>(camera, integrator, shapes);
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

    while (!glfwWindowShouldClose(window)) {
        renderer.run_one_iteration(scene);
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

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}