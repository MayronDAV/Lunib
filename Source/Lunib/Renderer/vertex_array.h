#pragma once
#include "Lunib/Core/base.h"
#include "buffer.h"

// std
#include <memory>



namespace Lunib
{
	class LUNIB_API VertexArray
	{
		public:
			virtual ~VertexArray() = default;

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual void SetVertexBuffer(VertexBuffer* p_vertexBuffer) = 0;
			virtual void SetIndexBuffer(IndexBuffer* p_indexBuffer) = 0;

			virtual VertexBuffer* GetVertexBuffer() = 0;
			virtual IndexBuffer* GetIndexBuffer() = 0;

			static VertexArray* Create();
	};

}