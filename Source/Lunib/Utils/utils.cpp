#include "utils.h"

// std
#include <iostream>

// lib
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize2.h>


namespace Lunib
{
	namespace Utils
	{
		static uint32_t s_MaxWidth  = 4096;
		static uint32_t s_MaxHeight = 4096;

		LUNIB_API uint32_t DataTypeSize(DataType p_type)
		{
			switch (p_type)
			{
				case DataType::None:    return 0;

				case DataType::Float:   return 4;
				case DataType::Float2:  return 4 * 2;
				case DataType::Float3:  return 4 * 3;
				case DataType::Float4:  return 4 * 4;

				case DataType::Mat3:    return 4 * 3 * 3;
				case DataType::Mat4:    return 4 * 4 * 4;

				case DataType::UInt:    return 4;
				case DataType::UInt2:   return 4 * 2;

				case DataType::Int:     return 4;
				case DataType::Int2:    return 4 * 2;
				case DataType::Int3:    return 4 * 3;
				case DataType::Int4:    return 4 * 4;
			}

			LERROR("Unknown DataType!");
			return 0;
		}

		LUNIB_API uint8_t DataTypeComponentCount(DataType p_type)
		{
			switch (p_type)
			{
				case DataType::None:    return 0;

				case DataType::Float:   return 1;
				case DataType::Float2:  return 2;
				case DataType::Float3:  return 3;
				case DataType::Float4:  return 4;

				case DataType::Mat3:    return 3 * 3;
				case DataType::Mat4:    return 4 * 4;

				case DataType::UInt:    return 1;
				case DataType::UInt2:   return 2;

				case DataType::Int:     return 1;
				case DataType::Int2:    return 2;
				case DataType::Int3:    return 3;
				case DataType::Int4:    return 4;
			}

			LERROR("Unknown DataType!");
			return 0;
		} 

		LUNIB_API uint8_t  TextureFormatToChannels(TextureFormat p_format)
		{
			switch (p_format)
			{
				case TextureFormat::R8:
				case TextureFormat::R32_INT:
					return 1;

				case TextureFormat::RG32_UINT:
					return 2;

				case TextureFormat::RGB8:
					return 3;

				case TextureFormat::RGBA8:
				case TextureFormat::RGBA32_FLOAT:
					return 4;
			}

			LERROR("Unknown texture format!");
			return 0;
		}

		LUNIB_API uint8_t  TextureFormatToBytesPerChannels(TextureFormat p_format)
		{
			switch (p_format)
			{
				case TextureFormat::R8:
				case TextureFormat::RGB8:
				case TextureFormat::RGBA8:
					return 1;

				case TextureFormat::R32_INT:
				case TextureFormat::RG32_UINT:
				case TextureFormat::RGBA32_FLOAT:
					return 4;
			}

			LERROR("Unknown texture format!");
			return 0;
		}

        LUNIB_API void GetMaxImageSize(uint32_t *p_width, uint32_t *p_height)
        {
			*p_width = s_MaxWidth;
			*p_height = s_MaxHeight;
        }

        LUNIB_API void SetMaxImageSize(uint32_t p_width, uint32_t p_height)
        {
			s_MaxWidth = p_width;
			s_MaxHeight = p_height;
        }

        LUNIB_API uint8_t *LoadImageFromFile(const char *p_path, uint32_t *p_width, uint32_t *p_height, uint32_t *p_channels, uint32_t *p_bytes, bool *p_isHDR, bool p_flipY)
        {
			stbi_set_flip_vertically_on_load(p_flipY);

			int texWidth = 0, texHeight = 0, texChannels = 0;
			stbi_uc* pixels	  = nullptr;
			int sizeOfChannel = 8;
			if (stbi_is_hdr(p_path))
			{
				sizeOfChannel = 32;
				pixels = (uint8_t*)stbi_loadf(p_path, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

				if (p_isHDR) *p_isHDR = true;
			}
			else
			{
				pixels = stbi_load(p_path, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

				if (p_isHDR) *p_isHDR = false;
			}

			if (!p_isHDR && s_MaxWidth > 0 && s_MaxHeight > 0 && ((uint32_t)texWidth > s_MaxWidth || (uint32_t)texHeight > s_MaxHeight))
			{
				uint32_t texWidthOld = texWidth, texHeightOld = texHeight;
				float aspectRatio = static_cast<float>(texWidth) / static_cast<float>(texHeight);
				if ((uint32_t)texWidth > s_MaxWidth)
				{
					texWidth = s_MaxWidth;
					texHeight = static_cast<uint32_t>(s_MaxWidth / aspectRatio);
				}
				if ((uint32_t)texHeight > s_MaxHeight)
				{
					texHeight = s_MaxHeight;
					texWidth = static_cast<uint32_t>(s_MaxHeight * aspectRatio);
				}

				int resizedChannels = texChannels;
				uint8_t* resizedPixels = (stbi_uc*)malloc(texWidth * texHeight * resizedChannels);

				if (p_isHDR)
				{
					stbir_resize_float_linear((float*)pixels, texWidthOld, texHeightOld, 0, (float*)resizedPixels, texWidth, texHeight, 0, STBIR_RGBA);
				}
				else
				{
					stbir_resize_uint8_linear(pixels, texWidthOld, texHeightOld, 0, resizedPixels, texWidth, texHeight, 0, STBIR_RGBA);
				}

				free(pixels);
				pixels = resizedPixels;
			}

			if (!pixels)
			{
				LERROR("Could not load image '{}'!", p_path);
				// Return magenta checkerboad image

				texChannels = 4;

				if (p_width)	*p_width	= 2;
				if (p_height)	*p_height	= 2;
				if (p_bytes)	*p_bytes	= sizeOfChannel / 8;
				if (p_channels) *p_channels = texChannels;

				const int32_t size = (*p_width) * (*p_height) * texChannels;
				uint8_t* data = new uint8_t[size];

				uint8_t datatwo[16] = {
					255, 0  , 255, 255,
					0,   0  , 0,   255,
					0,   0  , 0,   255,
					255, 0  , 255, 255
				};

				memcpy(data, datatwo, size);

				return data;
			}

			if (texChannels != 4)
				texChannels = 4;

			if (p_width)	*p_width	= texWidth;
			if (p_height)	*p_height	= texHeight;
			if (p_bytes)	*p_bytes	= sizeOfChannel / 8;
			if (p_channels) *p_channels = texChannels;

			const uint64_t size = uint64_t(texWidth) * uint64_t(texHeight) * uint64_t(texChannels) * uint64_t(sizeOfChannel / 8U);
			uint8_t* result = new uint8_t[size];
			memcpy(result, pixels, size);

			stbi_image_free(pixels);
			return result;
        }

    } // Lunib::Utils

	LUNIB_API void Destroy(void* p_ptr)
	{
		if (p_ptr != nullptr)
		{
			delete p_ptr;
			p_ptr = nullptr;
		}
	}

} // Lunib::Utils