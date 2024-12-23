#include "buffer.h"

#include "Lunib/Core/engine.h"
#include "Platform/OpenGL/opengl_buffer.h"


namespace Lunib
{
	VertexBuffer *VertexBuffer::Create(size_t p_size)
	{
        if (Engine::GetAPI() == RenderAPI::OpenGL)
            return new OpenGLVertexBuffer(p_size);

        return nullptr;
	}

	VertexBuffer *VertexBuffer::Create(const void* p_data, size_t p_size)
	{
        if (Engine::GetAPI() == RenderAPI::OpenGL)
            return new OpenGLVertexBuffer(p_data, p_size);

        return nullptr;
	}

	IndexBuffer *IndexBuffer::Create(uint32_t* p_indices, uint32_t p_count)
	{
        if (Engine::GetAPI() == RenderAPI::OpenGL)
            return new OpenGLIndexBuffer(p_indices, p_count);

        return nullptr;
	}

} // Lunib
