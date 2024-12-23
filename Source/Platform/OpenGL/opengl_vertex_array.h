#pragma once

#include "Lunib/Renderer/vertex_array.h"



namespace Lunib
{
	class OpenGLVertexArray : public VertexArray
	{
		public:
			OpenGLVertexArray();
			~OpenGLVertexArray() override;

			void Bind() const override;
			void Unbind() const override;

			void SetVertexBuffer(VertexBuffer* p_vertexBuffer) override;
			void SetIndexBuffer(IndexBuffer* p_indexBuffer) override;
	
			VertexBuffer* GetVertexBuffer() override { return m_VertexBuffer; }
			IndexBuffer* GetIndexBuffer() override { return m_IndexBuffer; }


		private:
			uint32_t m_RendererID;
			uint32_t m_VertexBufferIndex = 0;

			VertexBuffer* m_VertexBuffer;
			IndexBuffer* m_IndexBuffer;
	};


}
