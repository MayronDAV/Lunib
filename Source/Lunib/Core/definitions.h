#pragma once

// std
#include <cstdint>



namespace Lunib
{
	enum class ShaderType : uint8_t
	{
		Vertex = 0, Fragment
	};

	enum class RenderAPI : uint8_t
	{
		None = 0,
		OpenGL
	};

	enum class WindowMode : uint8_t
	{
		Windowed = 0,
		Fullscreen,
		Borderless
	};

	enum class CursorMode : uint8_t
	{
		Normal = 0, 
		Hidden,
		Disabled
	};

} // Lunib