#pragma once

#if __APPLE__
#include <TargetConditionals.h>
#endif

#if TARGET_OS_IPHONE

#include "avocado/renderer/opengl/shader/attribute.h"
#include "avocado/renderer/opengl/shader/shader.h"
#include "avocado/renderer/opengl/shader/uniform.h"

#else

#include "renderer/opengl/shader/attribute.h"
#include "renderer/opengl/shader/shader.h"
#include "renderer/opengl/shader/uniform.h"

#endif // TARGET_OS_IPHONE

#include <unordered_map>
#include <vector>

#include <glad/glad.h>

class Program
{
    std::string name;
    std::string error = "";
    std::vector<Shader> shaders;
    GLuint programId = 0;
    std::unordered_map<const char *, Attribute> attributes;
    std::unordered_map<const char *, Uniform> uniforms;

    void destroy();
    GLuint link(std::vector<Shader> &shaders);
    bool initialized;

public:
    Program(std::string name);
    ~Program();

    std::string getName() { return name; }

    bool load();
    std::string getError();

    GLuint get();
    bool use();
    Attribute getAttrib(const char *name);
    Uniform getUniform(const char *name);
};
