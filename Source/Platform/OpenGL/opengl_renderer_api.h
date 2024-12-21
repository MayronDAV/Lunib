#pragma once
#include "Lunib/Renderer/renderer_api.h"


namespace Lunib
{
    class LUNIB_API OpenGLRendererAPI : public RendererAPI
    {
        public:
            OpenGLRendererAPI() = default;
            ~OpenGLRendererAPI() override = default;

            void SetViewport(float p_x, float p_y, uint32_t p_width, uint32_t p_height) override;

			void ClearColor(const Vec4& p_color, bool p_clearDepth = true) override;
    };
    
} // Lunib
