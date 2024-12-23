#include "opengl_context.h"

// std
#include <iostream>

// lib
#include <glad/glad.h>


namespace Lunib
{
    Lunib::OpenGLContext::OpenGLContext(void *p_getProcAddress)
    {
        int status = gladLoadGLLoader((GLADloadproc)p_getProcAddress);
        assert(status && "Failed to initialize Glad!");
    }


} // Lunib
