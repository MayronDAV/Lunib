#pragma once
#include "Lunib/Core/base.h"
#include "Lunib/Core/definitions.h"

#include "Lunib/Utils/utils.h"

// std
#include <vector>
#include <string>


namespace Lunib
{
	struct LUNIB_API BufferElement
	{
		std::string Name    = "";
		DataType Type       = DataType::None;
		uint32_t Size       = 0;
		uint32_t Offset     = 0;
		bool Normalized     = false;

		BufferElement() {}
		BufferElement(DataType p_type, const std::string& p_name, bool p_normalized = false)
		:Name(p_name), Type(p_type), Size(Utils::DataTypeSize(p_type)),
			Offset(0), Normalized(p_normalized) 
		{}
	};


	class LUNIB_API BufferLayout
	{
		public:
			BufferLayout() {}
			BufferLayout(const std::initializer_list<BufferElement>& p_element)
				: m_Elements(p_element)
			{
				CalculateOffsetAndStride();
			}
			inline uint32_t GetStride() const { return m_Stride; }
			inline const std::vector<BufferElement>& GetElements() const { return m_Elements;  }

			std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
			std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
			std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
			std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

		private:
			void CalculateOffsetAndStride()
			{
				uint32_t offset = 0;
				m_Stride = 0;
				for (auto& element : m_Elements)
				{
					element.Offset = offset;
					offset += element.Size;
					m_Stride += element.Size;
				}
			}

		private:
			std::vector<BufferElement> m_Elements;
			uint32_t m_Stride = 0;
	};

	class LUNIB_API VertexBuffer
	{
		public:
			virtual ~VertexBuffer() = default;

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual const BufferLayout& GetLayout() const = 0;
			virtual void SetLayout(const BufferLayout& p_layout) = 0;

			virtual void SetData(const void* p_data, size_t p_size, size_t p_offset = 0ul) = 0;

			static VertexBuffer* Create(size_t p_size);
			static VertexBuffer* Create(const void* p_data, size_t p_size);
	};

	class LUNIB_API IndexBuffer
	{
		public:
			virtual ~IndexBuffer() = default;

			virtual uint32_t GetCount() const = 0;

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			static IndexBuffer* Create(uint32_t* p_indices, uint32_t p_count);

	};
}
