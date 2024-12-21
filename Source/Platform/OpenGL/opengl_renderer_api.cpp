#include "opengl_renderer_api.h"

// lib
#include <glad/glad.h>



namespace Lunib
{

    void OpenGLRendererAPI::SetViewport(float p_x, float p_y, uint32_t p_width, uint32_t p_height)
    {
        glViewport(int(p_x), int(p_y), p_width, p_height);
    }

    void OpenGLRendererAPI::ClearColor(const Vec4 &p_color, bool p_clearDepth)
    {
        glClearColor(p_color.r, p_color.g, p_color.b, p_color.a);
        GLbitfield mask = GL_COLOR_BUFFER_BIT;
        if (p_clearDepth)
            mask |= GL_DEPTH_BUFFER_BIT;

        glClear(mask);
    }

} // Lunib