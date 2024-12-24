#pragma once
#include "Lunib/Core/base.h"
#include "Lunib/Math/Ext/vector.h"
#include "Lunib/Core/definitions.h"
#include "vertex_array.h"
#include "buffer.h"


// std
#include <cstdint>


namespace Lunib
{
	class LUNIB_API RendererAPI
	{
		public:
			virtual ~RendererAPI() = default;

			static RendererAPI& Get();
			static void Init();
			static void Release();

			virtual void SetViewport(float p_x, float p_y, uint32_t p_width, uint32_t p_height) = 0;

			virtual void ClearColor(const Vec4& p_color, bool p_clearDepth = true) = 0;

			virtual void Draw(DrawType p_type, VertexArray* p_vertexArray, uint32_t p_vertexCount) = 0;
			virtual void DrawIndexed(DrawType p_type, VertexArray* p_vertexArray, uint32_t p_indexCount = 0) = 0;

		private:
			static RendererAPI* Create();

		private:
			static RendererAPI* s_Instance;
	};
	
} // Lunib

