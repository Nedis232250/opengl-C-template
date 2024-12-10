#pragma once
#include <gl/gl.h>
#include <stdint.h>
#include <iostream>


class Shader {
private:
    uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    void deconstructor_jump(uint32_t program) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        glDeleteProgram(program);

        std::cout << "Shaders cleaned up\n";
    }

public:
    uint32_t shader_program = glCreateProgram();
    
    Shader(const char* vertex_source, const char* fragment_source) {
        int32_t success;
        int32_t length = 0;

        glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
        glCompileShader(vertex_shader);

        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &length);
            char* error_msg = (char*)malloc(length * sizeof(char));

            glGetShaderInfoLog(vertex_shader, length, &length, error_msg);

            const char* error_copy = error_msg;
            free(error_msg);

            std::cout << "Error from Vertex Shader - " << error_copy << "\n";
            
            deconstructor_jump(shader_program);
            delete error_copy;
            
            throw std::runtime_error("Error Compiling Fragment Shader\n");
        }

        glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
        glCompileShader(fragment_shader);

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &length);
            char* error_msg = (char*)malloc(length * sizeof(char));

            glGetShaderInfoLog(fragment_shader, length, &length, error_msg);

            const char* error_copy = error_msg;
            free(error_msg);

            std::cout << "Error from Fragment Shader - " << error_copy << "\n";
            
            deconstructor_jump(shader_program);
            delete error_copy;

            throw std::runtime_error("Error Compiling Fragment Shader\n");
        }

        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);

        glLinkProgram(shader_program);
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &length);
            char* error_msg = (char*)malloc(length * sizeof(char));

            glGetProgramInfoLog(shader_program, length, &length, error_msg);

            const char* error_copy = error_msg;
            free(error_msg);

            std::cout << "Error Linking Program - " << error_copy << "\n";

            deconstructor_jump(shader_program);
            throw std::runtime_error("Error Linking Program\n");
        }

        glValidateProgram(shader_program);
        glGetProgramiv(shader_program, GL_VALIDATE_STATUS, &success);

        if (!success) {
            glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &length);
            char* error_msg = (char*)malloc(length * sizeof(char));

            glGetProgramInfoLog(shader_program, length, &length, error_msg);

            const char* error_copy = error_msg;
            free(error_msg);

            std::cout << "Error VaLidating Program - " << error_copy << "\n";

            deconstructor_jump(shader_program);
            throw std::runtime_error("Error Validating Program\n");
        }
    }

    ~Shader() {
        deconstructor_jump(shader_program);
    }
};
