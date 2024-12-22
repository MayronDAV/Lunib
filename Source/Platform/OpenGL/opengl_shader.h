#pragma once
#include "Lunib/Renderer/shader.h"

namespace Lunib
{
	class LUNIB_API OpenGLShader : public Shader
	{
		public:
			OpenGLShader(const std::unordered_map<ShaderType, std::vector<uint32_t>>& p_spirv);
			~OpenGLShader() override;

			void Bind() const override;
			void Unbind() const override;

			void PushValue(const std::string& p_name, void* p_value) override;

		private:
			void CreateProgram(const std::unordered_map<ShaderType, std::vector<uint32_t>>& p_spirv);

		private:
			uint32_t m_RendererID;
	};

} // Lunib
