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
		LUNIB_API uint8_t DataTypeComponentCount(DataType p_type);

	} // Lunib::Utils

	LUNIB_API void Destroy(void* p_ptr);

} // Lunib
