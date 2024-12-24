#include "texture_importer.h"
#include "Lunib/Utils/utils.h"





namespace Lunib
{
    LUNIB_API Texture2D *LoadTexture2D(const std::string &p_path)
    {
		TextureSpecification spec   = {};
		spec.WrapU					= TextureWrap::CLAMP_TO_EDGE;
		spec.WrapV					= TextureWrap::CLAMP_TO_EDGE;
		spec.MinFilter				= TextureFilter::LINEAR;
		spec.MagFilter				= TextureFilter::LINEAR;
		spec.AnisotropyEnable		= true;
		spec.GenerateMips			= true;

		return LoadTexture2D(p_path, spec);
    }

    LUNIB_API Texture2D *LoadTexture2D(const std::string &p_path, const TextureSpecification &p_spec)
    {
		uint32_t width, height, channels = 4, bytes = 1;
		bool isHDR					= false;
		uint8_t* data				= Utils::LoadImageFromFile(p_path.c_str(), &width, &height, &channels, &bytes, &isHDR);

		TextureSpecification spec   = p_spec;
		spec.Width					= width;
		spec.Height					= height;
		spec.Format					= (isHDR) ? TextureFormat::RGBA32_FLOAT : TextureFormat::RGBA8;
		spec.Usage					= TextureUsage::TEXTURE_SAMPLED;

		uint64_t imageSize			= uint64_t(width) * uint64_t(height) * uint64_t(channels) * uint64_t(bytes);
		auto texture		        = Texture2D::Create(spec, data, imageSize);
		if (!texture)
		{
			LERROR("Failed to create texture!")
			free(data);
			return nullptr;
		}

		free(data);
		return texture;
    }

} // Lunib
