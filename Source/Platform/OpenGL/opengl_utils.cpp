#include "opengl_utils.h"

// lib
#include <glad/glad.h>



namespace Lunib::GLUtils
{
    uint32_t TextureFormatToGLFormat(TextureFormat p_format)
    {
		switch (p_format)
		{
			case TextureFormat::R8:
			case TextureFormat::R32_INT:		
				return GL_RED;
			case TextureFormat::RG32_UINT:		
				return GL_RG;
			case TextureFormat::RGB8:   		
				return GL_RGB;
			case TextureFormat::RGBA32_FLOAT:
			case TextureFormat::RGBA8:  		
				return GL_RGBA;
		}

		LERROR("Unsupported texture format")
		return 0;
    }

    uint32_t Lunib::GLUtils::TextureFormatToGLInternalFormat(TextureFormat p_format)
    {
		switch (p_format)
		{
			case TextureFormat::R8:     		return GL_R8;
			case TextureFormat::R32_INT:		return GL_R32I;
			case TextureFormat::RG32_UINT:		return GL_RG32UI;
			case TextureFormat::RGBA32_FLOAT:	return GL_RGBA32F;
			case TextureFormat::RGB8:   		return GL_RGB8;
			case TextureFormat::RGBA8:  		return GL_RGBA8;
		}

		LERROR("Unsupported texture format")
		return 0;
    }

    uint32_t TextureFilterToGL(TextureFilter p_filter, bool p_mipmap /* = false */)
    {
        switch (p_filter)
        {
            case TextureFilter::LINEAR: return p_mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;
            case TextureFilter::NEAREST: return p_mipmap ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST;
        }

        LERROR("Unsupported texture filter")
		return 0;
    }

    uint32_t TextureWrapToGL(TextureWrap p_wrap)
    {
        switch (p_wrap)
        {
            case TextureWrap::REPEAT:           return GL_REPEAT;
            case TextureWrap::MIRRORED_REPEAT:  return GL_MIRRORED_REPEAT;
            case TextureWrap::CLAMP_TO_BORDER:  return GL_CLAMP_TO_BORDER;
            case TextureWrap::CLAMP_TO_EDGE:    return GL_CLAMP_TO_EDGE;
        }

        LERROR("Unsupported texture wrap")
		return 0;
    }

} // Lunib::GLUtils