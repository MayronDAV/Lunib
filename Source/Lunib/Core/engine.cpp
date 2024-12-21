#include "engine.h"


namespace Lunib
{
	RenderAPI Engine::s_RenderAPI = RenderAPI::OpenGL;

	RenderAPI Engine::GetAPI()
	{
		return s_RenderAPI;
	}

	void Engine::SetAPI(RenderAPI p_api)
	{
		s_RenderAPI = p_api;
	}

} // Lunib
