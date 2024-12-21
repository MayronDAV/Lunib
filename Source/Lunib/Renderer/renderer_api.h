#pragma once
#include "Lunib/Core/base.h"
#include "Lunib/Math/Ext/vector.h"

// std
#include <cstdint>


namespace Lunib
{
	class LUNIB_API RendererAPI
	{
		public:
			virtual ~RendererAPI() = default;

			static RendererAPI& Get();

			virtual void SetViewport(float p_x, float p_y, uint32_t p_width, uint32_t p_height) = 0;

			virtual void ClearColor(const Vec4& p_color, bool p_clearDepth = true) = 0;

		private:
			static RendererAPI* Create();

		private:
			static RendererAPI* s_Instance;
	};
	
} // Lunib

