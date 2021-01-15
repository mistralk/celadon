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

using namespace celadon;

int width = 600, height = 400;
const int max_spp = 0;

int main() {
    auto image = std::make_shared<celadon::Image>(width, height);
    auto scene = Scene::make_test_scene(width, height);
    celadon::Renderer renderer(image);
    renderer.setup();
    
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

        if (image->get_spp() < max_spp || !max_spp) {
            timer.start();
            //--------------------------------
            renderer.run_one_iteration(scene);
            //--------------------------------
            timer.end();
            iteration++;
            accumulated_time += timer.elapsed();
        }

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