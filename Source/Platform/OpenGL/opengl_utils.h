#pragma once
#include "Lunib/Core/base.h"
#include "Lunib/Core/definitions.h"


namespace Lunib::GLUtils
{
    uint32_t TextureFormatToGLFormat(TextureFormat p_format);
    uint32_t TextureFormatToGLInternalFormat(TextureFormat p_format);
    uint32_t TextureFilterToGL(TextureFilter p_filter, bool p_mipmap = false);
    uint32_t TextureWrapToGL(TextureWrap p_wrap);

} // Lunib