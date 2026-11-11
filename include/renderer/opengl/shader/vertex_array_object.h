#pragma once

#include <glad/glad.h>

class VertexArrayObject
{
    GLuint id;

public:
    static GLuint currentId;

    VertexArrayObject();
    ~VertexArrayObject();

    void bind();
    GLuint get();
};