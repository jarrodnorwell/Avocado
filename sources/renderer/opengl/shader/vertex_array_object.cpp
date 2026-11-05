#if __APPLE__
#include <TargetConditionals.h>
#endif

#if TARGET_OS_IPHONE

#include "avocado/renderer/opengl/shader/vertex_array_object.h"

#else

#include "renderer/opengl/shader/vertex_array_object.h"

#endif // TARGET_OS_IPHONE

GLuint VertexArrayObject::currentId = 0;

VertexArrayObject::VertexArrayObject() { glGenVertexArrays(1, &id); }

VertexArrayObject::~VertexArrayObject() { glDeleteVertexArrays(1, &id); }

void VertexArrayObject::bind() {
    if (currentId != id) {
        currentId = id;
        glBindVertexArray(id);
    }
}

GLuint VertexArrayObject::get() { return id; }