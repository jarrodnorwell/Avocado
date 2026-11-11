#pragma once

#if __APPLE__
#include <TargetConditionals.h>
#endif

#if TARGET_OS_IPHONE

#include "avocado/config.h"

#else

#include "config.h"

#endif // TARGET_OS_IPHONE

#include <optional>
#include <string>

#include <glad/glad.h>

struct Image
{
    GLuint id;
    int w;
    int h;

    Image(GLuint id, int w, int h);
};

std::optional<Image> getImage(const std::string &image, const std::string &path = avocado::assetsPath());