#pragma once
#include "Lunib/Renderer/renderer_api.h"


namespace Lunib
{
	class OpenGLRendererAPI : public RendererAPI
	{
		public:
			OpenGLRendererAPI();
			~OpenGLRendererAPI() override = default;

			void SetViewport(float p_x, float p_y, uint32_t p_width, uint32_t p_height) override;

			void ClearColor(const Vec4& p_color, bool p_clearDepth = true) override;

			void Draw(DrawType p_type, VertexArray* p_vertexArray, uint32_t p_vertexCount) override;
			void DrawIndexed(DrawType p_type, VertexArray* p_vertexArray, uint32_t p_indexCount) override;
	};
	
} // Lunib
