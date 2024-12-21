#pragma once

#include "Lunib/Renderer/graphics_context.h"


namespace Lunib
{
	class OpenGLContext : public GraphicsContext
	{
		public:
			OpenGLContext(void* p_getProcAddress);

			void Init() override {}
			void SwapBuffers() override {}
	};

}
