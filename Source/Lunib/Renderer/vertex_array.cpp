#include "vertex_array.h"

#include "Lunib/Core/engine.h"
#include "Platform/OpenGL/opengl_vertex_array.h"



namespace Lunib
{
    VertexArray* VertexArray::Create()
    {
        if (Engine::GetAPI() == RenderAPI::OpenGL)
            return new OpenGLVertexArray();

        return nullptr;
    }

} // Lunib