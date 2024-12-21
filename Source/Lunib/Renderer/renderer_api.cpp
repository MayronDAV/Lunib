#include "renderer_api.h"

#include "Lunib/Core/engine.h"
#include "Platform/OpenGL/opengl_renderer_api.h"


namespace Lunib
{
    RendererAPI* RendererAPI::s_Instance = nullptr;

    RendererAPI& RendererAPI::Get()
    {
        if (!s_Instance)
            s_Instance = Create();

        return *s_Instance;
    }

    RendererAPI* RendererAPI::Create()
    {
        if (Engine::GetAPI() == RenderAPI::OpenGL)
            return new OpenGLRendererAPI();

        return nullptr;
    }

} // Lunib