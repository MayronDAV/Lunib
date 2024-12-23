#include "opengl_renderer_api.h"

// std
#include <iostream>

// lib
#include <glad/glad.h>



namespace Lunib
{
    static GLenum DrawTypeToOpenGL(DrawType p_type)
    {
        switch (p_type)
        {
            case DrawType::Points:         return GL_POINTS;
            case DrawType::Lines:          return GL_LINES;
            case DrawType::LineStrip:      return GL_LINE_STRIP;
            case DrawType::LineLoop:       return GL_LINE_LOOP;
            case DrawType::Triangles:      return GL_TRIANGLES;
            case DrawType::TriangleStrip:  return GL_TRIANGLE_STRIP;
            case DrawType::TriangleFan:    return GL_TRIANGLE_FAN;
        }

        LERROR("Unknown DrawType!");
        return 0;
    }

    static void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
            case GL_DEBUG_SEVERITY_HIGH:         LFATAL(message); return;
            case GL_DEBUG_SEVERITY_MEDIUM:       LERROR(message); return;
            case GL_DEBUG_SEVERITY_LOW:          LWARN (message); return;
            case GL_DEBUG_SEVERITY_NOTIFICATION: LTRACE(message); return;
		}
	}

    OpenGLRendererAPI::OpenGLRendererAPI()
    {
    #ifdef LUNIB_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_LINE_SMOOTH);
    }

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

    void OpenGLRendererAPI::Draw(DrawType p_type, VertexArray* p_vertexArray, uint32_t p_vertexCount)
    {
        if (p_vertexArray)
            p_vertexArray->Bind();
        glDrawArrays(DrawTypeToOpenGL(p_type), 0, p_vertexCount);
    }

    void OpenGLRendererAPI::DrawIndexed(DrawType p_type, VertexArray* p_vertexArray, uint32_t p_indexCount)
    {
		uint32_t count = 0;
        if (p_vertexArray) {
            p_vertexArray->Bind();
        	count = (p_indexCount == 0) ? p_vertexArray->GetIndexBuffer()->GetCount() : p_indexCount;
		}
		else
			count = p_indexCount;

		if (count == 0)
		{
			LERROR("Index count is 0!");
			return;
		}

        glDrawElements(DrawTypeToOpenGL(p_type), count, GL_UNSIGNED_INT, nullptr);
    }

} // Lunib