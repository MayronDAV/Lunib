#pragma once

#include "Lunib/Core/base.h"
#include "texture.h"



namespace Lunib
{
    LUNIB_API Texture2D* LoadTexture2D(const std::string& p_path);
	LUNIB_API Texture2D* LoadTexture2D(const std::string& p_path, const TextureSpecification& p_spec);


} // Lunib