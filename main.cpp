#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdint.h>
#include "file.h"
#include "shader.h"
#include "buffer.h"

float x_angle = 0.0f;
float y_angle = 0.0f;
float z_angle = 0.0f;

GLFWwindow* initalize_GLFW_GLEW() {
    if (!glfwInit()) {
        std::cout << "GLFW initialization failed\n";
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(720, 720, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cout << "Window creation failed\n";
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initalization failed\n";
        return nullptr;
    }

    return window;
}

int main() {
    GLFWwindow* window = initalize_GLFW_GLEW();
    if (!window) {
        return -1;
    }

    float vertices[] = {
        -0.25f, 0.25f, 0.0, 1.0, 0.0, 0.0, 1.0,
        0.25f, -0.25f, 0.0, 0.0, 1.0, 0.0, 1.0,
        -0.25f, -0.25f, 0.0, 0.0, 0.0, 1.0, 1.0,
        0.25f, 0.25f, 0.0, 0.0, 0.0, 1.0, 1.0
    };

    uint32_t indices[] = {
        0, 1, 2,
        0, 1, 3
    };

    Shader shader(read_file("vrtx.txt").c_str(), read_file("frag.txt").c_str());
    uint32_t shader_program = shader.shader_program;

    Buffer<float> vertex(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    Buffer<uint32_t> index(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));

    glEnableVertexAttribArray(glGetAttribLocation(shader_program, "vpos"));
    glEnableVertexAttribArray(glGetAttribLocation(shader_program, "vrgba"));

    glVertexAttribPointer(glGetAttribLocation(shader_program, "vpos"), 3, GL_FLOAT, 0, 7 * sizeof(float), (const void*)0);
    glVertexAttribPointer(glGetAttribLocation(shader_program, "vrgba"), 4, GL_FLOAT, 0, 7 * sizeof(float), (const void*)(3 * sizeof(float)));

    glUseProgram(shader_program);

    glUniform1f(glGetUniformLocation(shader_program, "x_angle"), x_angle);
    glUniform1f(glGetUniformLocation(shader_program, "y_angle"), y_angle);
    glUniform1f(glGetUniformLocation(shader_program, "z_angle"), z_angle);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawElements(GL_TRIANGLES, (int32_t)((float)sizeof(indices) / sizeof(uint32_t)), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDisableVertexAttribArray(glGetAttribLocation(shader_program, "vpos"));
    glDisableVertexAttribArray(glGetAttribLocation(shader_program, "vrgba"));
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
