#include "renderer_api.h"

#include "Lunib/Core/engine.h"
#include "Platform/OpenGL/opengl_renderer_api.h"


namespace Lunib
{
    RendererAPI* RendererAPI::s_Instance = nullptr;

    RendererAPI& RendererAPI::Get()
    {
        Init();

        return *s_Instance;
    }

    void RendererAPI::Init()
    {
        if (!s_Instance)
            s_Instance = Create();
    }

    void RendererAPI::Release()
    {
        if (s_Instance)
        {
            delete s_Instance;
            s_Instance = nullptr;
        }
    }

    RendererAPI* RendererAPI::Create()
    {
        if (Engine::GetAPI() == RenderAPI::OpenGL)
            return new OpenGLRendererAPI();

        return nullptr;
    }

} // Lunib