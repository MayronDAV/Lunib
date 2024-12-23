#pragma once
#include "Lunib/Renderer/shader.h"

namespace Lunib
{
	class OpenGLShader : public Shader
	{
		public:
			OpenGLShader(const std::unordered_map<ShaderType, std::vector<uint32_t>>& p_spirv);
			OpenGLShader(const ShaderSource& p_source);
			~OpenGLShader() override;

			void Bind() const override;
			void Unbind() const override;

			void SetMat4(const std::string& p_name, const Mat4& p_value) override;
			void SetMat3(const std::string& p_name, const Mat3& p_value) override;
			void SetVec2(const std::string& p_name, const Vec2& p_value) override;
			void SetVec3(const std::string& p_name, const Vec3& p_value) override;
			void SetVec4(const std::string& p_name, const Vec4& p_value) override;

		private:
			void CreateProgram(const std::unordered_map<ShaderType, std::vector<uint32_t>>& p_spirv);
			void CreateProgram(const ShaderSource& p_source);

		private:
			uint32_t m_RendererID;
	};

} // Lunib
