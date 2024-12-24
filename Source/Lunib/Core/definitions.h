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

	enum class TextureUsage : uint8_t
	{
		TEXTURE_SAMPLED = 0,
		TEXTURE_STORAGE,
		TEXTURE_COLOR_ATTACHMENT,
		TEXTURE_DEPTH_STENCIL_ATTACHMENT,
	};

	enum class TextureFormat : uint8_t
	{
		None = 0,

		// Color

		R8,
		R32_INT,
		RG32_UINT,	
		RGB8,	
		RGBA8,
		RGBA32_FLOAT,

		// Depth

		D16,
		D32_FLOAT,

		// Depth Stencil
		
		D16_S8_UINT,
		D24_S8_UINT,
		D32_FLOAT_S8_UINT,
	};

	enum class TextureFilter : uint8_t
	{
		NONE = 0,
		LINEAR,
		NEAREST
	};

	enum class TextureWrap : uint8_t
	{
		NONE = 0,
		REPEAT,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER
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