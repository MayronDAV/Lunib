#pragma once
#include "base.h"
#include "definitions.h"



namespace Lunib
{
	class LUNIB_API Engine
	{
		public:
			static RenderAPI GetAPI();
			
			static void SetAPI(RenderAPI p_api);

		private:
			static RenderAPI s_RenderAPI;
	};


} // Lunib
