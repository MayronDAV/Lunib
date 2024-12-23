#include "opengl_vertex_array.h"
#include "Lunib/Core/definitions.h"
#include "Lunib/Utils/utils.h"

// std
#include <iostream>
#include <cassert>
#include <cstdint>

// lib
#include <glad/glad.h>




namespace Lunib
{
	static GLenum DataTypeToOpenGLBaseType(DataType p_type)
	{
		switch (p_type)
		{
			case DataType::Float:	return GL_FLOAT;
			case DataType::Float2:	return GL_FLOAT;
			case DataType::Float3:	return GL_FLOAT;
			case DataType::Float4:	return GL_FLOAT;

			case DataType::Mat3:	return GL_FLOAT;
			case DataType::Mat4:	return GL_FLOAT;

			case DataType::UInt:	return GL_UNSIGNED_INT;
			case DataType::UInt2:	return GL_UNSIGNED_INT;

			case DataType::Int:		return GL_INT;
			case DataType::Int2:	return GL_INT;
			case DataType::Int3:	return GL_INT;
			case DataType::Int4:	return GL_INT;
		}

		LERROR("Unknown DataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::SetVertexBuffer(VertexBuffer* p_vertexBuffer)
	{
		assert(p_vertexBuffer->GetLayout().GetElements().size() > 0 && "p_vertexBuffer has NULL layout");

		glBindVertexArray(m_RendererID);
		p_vertexBuffer->Bind();


		uint32_t index = 0;
		const auto& layout = p_vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			uint8_t count = Utils::DataTypeComponentCount(element.Type);
			switch (element.Type)
			{
				case DataType::Float:
				case DataType::Float2:
				case DataType::Float3:
				case DataType::Float4:
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						count,
						DataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(const uint64_t)element.Offset);
					m_VertexBufferIndex++;
					break;
				}
				case DataType::UInt:
				case DataType::UInt2:
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribIPointer(m_VertexBufferIndex,
						count,
						DataTypeToOpenGLBaseType(element.Type), 
						layout.GetStride(),
						(const void*)(const uint64_t)element.Offset);
					break;
				}
				case DataType::Int:
				case DataType::Int2:
				case DataType::Int3:
				case DataType::Int4:
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribIPointer(m_VertexBufferIndex,
						count,
						DataTypeToOpenGLBaseType(element.Type),
						layout.GetStride(),
						(const void*)(const uint64_t)element.Offset);
					m_VertexBufferIndex++;
					break;
				}
				case DataType::Mat3:
				case DataType::Mat4:
				{
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(m_VertexBufferIndex);
						glVertexAttribPointer(m_VertexBufferIndex,
							count,
							DataTypeToOpenGLBaseType(element.Type),
							element.Normalized ? GL_TRUE : GL_FALSE,
							layout.GetStride(),
							(const void*)(element.Offset + sizeof(float) * count * i));
						glVertexAttribDivisor(m_VertexBufferIndex, 1);
						m_VertexBufferIndex++;
					}
					break;
				}
				default:
					LERROR("Unknown DataType!");
					break;
			}
		}

		m_VertexBuffer = p_vertexBuffer;
	}

	void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* p_indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		p_indexBuffer->Bind();
		m_IndexBuffer = p_indexBuffer;
	}

}
