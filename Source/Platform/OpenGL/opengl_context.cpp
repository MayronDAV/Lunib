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
        if (!status)
        {
            std::cerr << "Failed to initialize Glad!\n";
            exit(1);
        }
    }


} // Lunib
