#include "utils.h"

// std
#include <iostream>


namespace Lunib
{
	namespace Utils
	{
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
	} // Lunib::Utils

	LUNIB_API void Destroy(void* p_ptr)
	{
		if (p_ptr)
		{
			delete p_ptr;
			p_ptr = nullptr;
		}
	}

} // Lunib::Utils