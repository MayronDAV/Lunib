#pragma once

#include "Lunib/Renderer/buffer.h"


namespace Lunib
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
		public:
			OpenGLVertexBuffer(size_t p_size);
			OpenGLVertexBuffer(const void* p_data, size_t p_size);
			~OpenGLVertexBuffer() override;

			void Bind() const override;
			void Unbind() const override;

			void SetData(const void* data, size_t size, size_t p_offset = 0ul) override;

			const BufferLayout& GetLayout() const override { return m_Layout; }
			void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

		private:
			uint32_t m_RendererID;
			BufferLayout m_Layout;
	};



	class OpenGLIndexBuffer : public IndexBuffer
	{
		public:
			OpenGLIndexBuffer(uint32_t* p_indices, uint32_t p_count);
			~OpenGLIndexBuffer() override;

			uint32_t GetCount() const override { return m_Count; }

			void Bind() const override;
			void Unbind() const override;

		private:
			uint32_t m_RendererID;
			uint32_t m_Count;
	};


}