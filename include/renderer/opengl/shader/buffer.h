#pragma once

#include <cstddef>

#include <glad/glad.h>

class Buffer
{
    GLuint id;

public:
    static GLuint currentId;

    Buffer(size_t size);
    ~Buffer();

    void update(int size, const void *data);
    void bind();
    GLuint get();
};