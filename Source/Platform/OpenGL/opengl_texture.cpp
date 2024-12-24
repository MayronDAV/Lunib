#include "opengl_texture.h"
#include "Lunib/Utils/utils.h"
#include "opengl_utils.h"

// lib
#include <glad/glad.h>



namespace Lunib
{
	OpenGLTexture2D::OpenGLTexture2D(const TextureSpecification &p_spec)
	{
		Init(p_spec);
	}

	OpenGLTexture2D::OpenGLTexture2D(const TextureSpecification &p_spec, const uint8_t *p_data, size_t p_size)
	{
		Init(p_spec);

		SetData(p_data, p_size);
	}


	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Init(const TextureSpecification &p_spec)
    {
		m_Format 			= GLUtils::TextureFormatToGLFormat(p_spec.Format);
		m_InternalFormat 	= GLUtils::TextureFormatToGLInternalFormat(p_spec.Format);
		m_Channels		 	= Utils::TextureFormatToChannels(p_spec.Format);
		m_BytesPerChannels 	= Utils::TextureFormatToBytesPerChannels(p_spec.Format);
		m_Width 			= p_spec.Width;
		m_Height 			= p_spec.Height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, 		GLUtils::TextureWrapToGL(p_spec.WrapU));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, 		GLUtils::TextureWrapToGL(p_spec.WrapV));
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, 	GLUtils::TextureFilterToGL(p_spec.MinFilter, p_spec.GenerateMips));
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, 	GLUtils::TextureFilterToGL(p_spec.MagFilter));


		if (p_spec.AnisotropyEnable && GLAD_GL_EXT_texture_filter_anisotropic)
		{
			GLfloat maxAnisotropy = 0.0f;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxAnisotropy);
			GLfloat value = std::min(4.0f, maxAnisotropy);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, value);
		}

		if (p_spec.GenerateMips)
		{
			glBindTexture(GL_TEXTURE_2D, m_RendererID);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
    }

	void OpenGLTexture2D::Resize(uint32_t p_width, uint32_t p_height)
	{
		uint32_t newTexID;
		glCreateTextures(GL_TEXTURE_2D, 1, &newTexID);
		glTextureStorage2D(newTexID, 1, m_InternalFormat, p_width, p_height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, 		GLUtils::TextureWrapToGL(m_Specification.WrapU));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, 		GLUtils::TextureWrapToGL(m_Specification.WrapV));
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, 	GLUtils::TextureFilterToGL(m_Specification.MinFilter, m_Specification.GenerateMips));
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, 	GLUtils::TextureFilterToGL(m_Specification.MagFilter));


		GLuint fboIDs[2] = { 0 };
		glGenFramebuffers(2, fboIDs);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, fboIDs[0]);
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER, 
			GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RendererID, 0);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboIDs[1]);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, newTexID, 0);

		glBlitFramebuffer(0, 0, m_Width, m_Height,
			0, 0, p_width, p_height,
			GL_COLOR_BUFFER_BIT, GL_LINEAR);

		glDeleteTextures(1, &m_RendererID);
		glDeleteFramebuffers(2, fboIDs);

		m_RendererID = newTexID;
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	void OpenGLTexture2D::Bind(uint32_t p_slot)
	{
		m_Slot = p_slot;
		glBindTextureUnit(p_slot, m_RendererID);
	}

	void OpenGLTexture2D::Unbind()
	{
		glBindTextureUnit(m_Slot, 0);
	}

	void OpenGLTexture2D::SetData(const uint8_t *p_data, size_t p_size)
    {
		assert((p_size >= (m_Width * m_Height * m_Channels * m_BytesPerChannels)) && "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_Format, GL_UNSIGNED_BYTE, p_data);
    }

} // Lunib