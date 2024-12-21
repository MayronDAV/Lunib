#pragma once

namespace Lunib
{
	enum class RenderAPI
	{
		None = 0,
		OpenGL
	};

	enum class WindowMode
	{
		Windowed = 0,
		Fullscreen,
		Borderless
	};

	enum class CursorMode
	{
		Normal = 0, 
		Hidden,
		Disabled
	};

} // Lunib