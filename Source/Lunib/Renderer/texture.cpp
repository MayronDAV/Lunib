#include "texture.h"
#include "Lunib/Core/engine.h"
#include "Platform/OpenGL/opengl_texture.h"



namespace Lunib
{
    Texture2D *Texture2D::Create(const TextureSpecification &p_spec)
    {
		if (Engine::GetAPI() == RenderAPI::OpenGL)
			return new OpenGLTexture2D(p_spec);

		return nullptr;
    }

    Texture2D *Texture2D::Create(const TextureSpecification &p_spec, const uint8_t *p_data, size_t p_size)
    {
		if (Engine::GetAPI() == RenderAPI::OpenGL)
			return new OpenGLTexture2D(p_spec, p_data, p_size);

		return nullptr;
    }

} // Lunib