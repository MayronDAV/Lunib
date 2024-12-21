#pragma once
#include "Lunib/Core/base.h"


namespace Lunib
{
	class LUNIB_API GraphicsContext
	{
		public:
			virtual ~GraphicsContext() = default;

			virtual void Init() = 0;
			virtual void SwapBuffers() = 0;
	};
}