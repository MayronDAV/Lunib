#pragma once

#include "Lunib/Core/base.h"
#include "Lunib/Core/definitions.h"

// std
#include <string>



namespace Lunib
{
	struct LUNIB_API TextureSpecification
	{
		uint32_t Width                      = 1;
		uint32_t Height                     = 1;
        TextureUsage Usage					= TextureUsage::TEXTURE_SAMPLED;
		TextureFormat Format                = TextureFormat::RGBA8;
        TextureFilter MinFilter				= TextureFilter::LINEAR;
		TextureFilter MagFilter				= TextureFilter::LINEAR;
		TextureWrap WrapU					= TextureWrap::REPEAT;
		TextureWrap WrapV					= TextureWrap::REPEAT;
		TextureWrap WrapW					= TextureWrap::REPEAT;
		bool GenerateMips                   = true;
        bool AnisotropyEnable				= true;

        const std::string DebugName         = "Texture";
	};

	class LUNIB_API Texture
	{
		public:
			virtual ~Texture() = default;

			virtual uint32_t GetWidth() const = 0;
			virtual uint32_t GetHeight() const = 0;
			virtual uint32_t GetChannels() const = 0;
            virtual uint32_t GetBytesPerChannels() const = 0;
			virtual uint32_t GetRendererID() = 0;

			virtual uint64_t GetEstimatedSize() const = 0;

			virtual const TextureSpecification& GetSpecification() const = 0;

			virtual void Bind(uint32_t p_slot = 0) = 0;
			virtual void Unbind() = 0;

            virtual void SetData(const uint8_t* p_data, size_t p_size) = 0;

			virtual bool operator== (const Texture& p_other) const = 0;

            static bool IsDepthStencilFormat(TextureFormat p_format)
			{
				return  p_format == TextureFormat::D24_S8_UINT || p_format == TextureFormat::D16_S8_UINT ||
					    p_format == TextureFormat::D32_FLOAT_S8_UINT;
			}

			static bool IsDepthFormat(TextureFormat p_format)
			{
				return  p_format == TextureFormat::D16 || p_format == TextureFormat::D32_FLOAT ||
					    p_format == TextureFormat::D24_S8_UINT || p_format == TextureFormat::D16_S8_UINT ||
					    p_format == TextureFormat::D32_FLOAT_S8_UINT;
			}

			static bool IsStencilFormat(TextureFormat p_format)
			{
				return  p_format == TextureFormat::D24_S8_UINT || p_format == TextureFormat::D16_S8_UINT ||
					    p_format == TextureFormat::D32_FLOAT_S8_UINT;
			}

            bool IsSampled() const { return GetSpecification().Usage == TextureUsage::TEXTURE_SAMPLED; }
			bool IsColorAttachment() const { return GetSpecification().Usage == TextureUsage::TEXTURE_COLOR_ATTACHMENT; }
			bool IsDepthStencilAttachment() const { return GetSpecification().Usage == TextureUsage::TEXTURE_DEPTH_STENCIL_ATTACHMENT; }

	};


	class LUNIB_API Texture2D : public Texture
	{
		public:
            static Texture2D* Create(const TextureSpecification& p_spec);
			static Texture2D* Create(const TextureSpecification& p_spec, const uint8_t* p_data, size_t p_size);
			
			virtual void Resize(uint32_t p_width, uint32_t p_height) = 0;
	};

}
