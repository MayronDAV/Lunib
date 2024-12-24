#pragma once
#include "Lunib/Core/base.h"
#include "Lunib/Core/definitions.h"

// std
#include <cstdint>


namespace Lunib
{
	namespace Utils
	{
		LUNIB_API uint32_t DataTypeSize(DataType p_type);
		LUNIB_API uint8_t  DataTypeComponentCount(DataType p_type);
		LUNIB_API uint8_t  TextureFormatToChannels(TextureFormat p_format);
		LUNIB_API uint8_t  TextureFormatToBytesPerChannels(TextureFormat p_format);
		
		LUNIB_API void GetMaxImageSize(uint32_t* p_width, uint32_t* p_height);
		LUNIB_API void SetMaxImageSize(uint32_t p_width, uint32_t p_height);
		LUNIB_API uint8_t* LoadImageFromFile(const char* p_path, uint32_t* p_width, uint32_t* p_height, uint32_t* p_channels, uint32_t* p_bytes, bool* p_isHDR = nullptr, bool p_flipY = true);


	} // Lunib::Utils

	LUNIB_API void Destroy(void* p_ptr);

} // Lunib
