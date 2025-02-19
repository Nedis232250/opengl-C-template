#pragma once
#include <GL/glew.h>
#include <stdint.h>
#include <iostream>

template<typename T> class Buffer {
private:
    uint32_t buffer;

public:
	Buffer(uint32_t target, T* data, size_t size) {
        glGenBuffers(1, &buffer);
        glBindBuffer(target, buffer);
        glBufferData(target, size, data, GL_STATIC_DRAW);
    }

    uint32_t get_buffer() {
        return buffer;
    }

    void set_buffer(uint32_t target, T* data, size_t size) {
        glGenBuffers(1, &buffer);
        glBindBuffer(target, buffer);
        glBufferData(target, size, data, GL_STATIC_DRAW);
    }

    ~Buffer() {
        glDeleteBuffers(1, &buffer);
    }
};

template<typename T> void edit_buffer(uint32_t buffer, uint32_t target, T* data, size_t size) {
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, GL_STATIC_DRAW);
}
