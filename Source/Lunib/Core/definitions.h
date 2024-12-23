#pragma once

// std
#include <cstdint>



namespace Lunib
{
	enum class RenderAPI : uint8_t
	{
		None = 0,
		OpenGL
	};

	enum class DataType : uint8_t
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		UInt, UInt2, UInt3, UInt4,
		Int, Int2, Int3, Int4
	};

	enum class ShaderType : uint8_t
	{
		Vertex = 0, Fragment
	};

	enum class DrawType : uint8_t
	{
		Points = 0,
		Lines,
		LineStrip,
		LineLoop,
		Triangles,
		TriangleStrip,
		TriangleFan
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