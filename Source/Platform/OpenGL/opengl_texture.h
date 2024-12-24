#pragma once
#include "Lunib/Renderer/texture.h"

// std
#include <vector>



namespace Lunib
{

	class LUNIB_API OpenGLTexture2D : public Texture2D
	{
		public:
			OpenGLTexture2D(const TextureSpecification& p_spec = {});
			OpenGLTexture2D(const TextureSpecification& p_spec, const uint8_t* p_data, size_t p_size);
			~OpenGLTexture2D() override;

			void Resize(uint32_t p_width, uint32_t p_height) override;

			uint32_t GetWidth() const override { return m_Width; }
			uint32_t GetHeight() const override { return m_Height; }
			uint32_t GetChannels() const override { return m_Channels; }
			uint32_t GetBytesPerChannels() const override { return m_BytesPerChannels; }
			uint32_t GetRendererID() override { return m_RendererID; }

			uint64_t GetEstimatedSize() const override { return m_Width * m_Height * m_Channels * m_BytesPerChannels; }

			const TextureSpecification& GetSpecification() const override { return m_Specification; }

			void Bind(uint32_t p_slot = 0) override;
			void Unbind() override;

			void SetData(const uint8_t* p_data, size_t p_size) override;

			bool operator== (const Texture& p_other) const override
			{
				return m_RendererID == ((OpenGLTexture2D&)p_other).m_RendererID;
			}

		private:
			void Init(const TextureSpecification& p_spec);

		private:
			TextureSpecification m_Specification;

			uint32_t m_Width			= NULL;
			uint32_t m_Height			= NULL;
			uint32_t m_Channels			= NULL;
			uint32_t m_BytesPerChannels = NULL;
			uint32_t m_RendererID		= NULL;
			uint32_t m_Slot 			= 0;

			uint32_t m_InternalFormat, m_Format;
	};

} // Lunib
