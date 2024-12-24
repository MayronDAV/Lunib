#include "opengl_shader.h"

// std
#include <iostream>

// lib
#include <glad/glad.h>


namespace Lunib
{

	static GLenum ShaderTypeToOpenGL(ShaderType p_type)
	{
		switch (p_type)
		{
			case ShaderType::Vertex:    return GL_VERTEX_SHADER;
			case ShaderType::Fragment:  return GL_FRAGMENT_SHADER;
		}

		return 0;
	}

	OpenGLShader::OpenGLShader(const std::unordered_map<ShaderType, std::vector<uint32_t>>& p_spirv)
	{
		CreateProgram(p_spirv);
	}

    OpenGLShader::OpenGLShader(const ShaderSource &p_source)
    {
		CreateProgram(p_source);
    }

    OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

    void OpenGLShader::SetInt(const std::string &p_name, int p_value)
    {
		std::string name = p_name;
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(m_RendererID, p_value);
    }

    void OpenGLShader::SetMat4(const std::string &p_name, const Mat4 &p_value)
    {
		std::string name = p_name;
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, &p_value[0][0]);
    }

    void OpenGLShader::SetMat3(const std::string &p_name, const Mat3 &p_value)
    {
		auto location = glGetUniformLocation(m_RendererID, p_name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, &p_value[0][0]);
    }

    void OpenGLShader::SetVec2(const std::string &p_name, const Vec2 &p_value)
    {
		auto location = glGetUniformLocation(m_RendererID, p_name.c_str());
		glUniform2f(location, p_value.x, p_value.y);
    }

    void OpenGLShader::SetVec3(const std::string &p_name, const Vec3 &p_value)
    {
		auto location = glGetUniformLocation(m_RendererID, p_name.c_str());
		glUniform3f(location, p_value.x, p_value.y, p_value.z);
    }

    void OpenGLShader::SetVec4(const std::string &p_name, const Vec4 &p_value)
    {
		auto location = glGetUniformLocation(m_RendererID, p_name.c_str());
		glUniform4f(location, p_value.x, p_value.y, p_value.z, p_value.w);
    }

    void OpenGLShader::CreateProgram(const std::unordered_map<ShaderType, std::vector<uint32_t>>& p_spirv)
	{
		GLuint program = glCreateProgram();

		std::vector<GLuint> shaderIDs;
		for (auto&& [stage, spirv] : p_spirv)
		{
			GLuint shaderID = glCreateShader(ShaderTypeToOpenGL(stage));
			glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t));
			glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
			glAttachShader(program, shaderID);
			shaderIDs.push_back(shaderID);
		}

		glLinkProgram(program);

		GLint isLinked;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);

			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
			LERROR("Shader linking failed: {}", infoLog.data());

			for (auto id : shaderIDs)
				glDeleteShader(id);

			return;
		}

		for (auto id : shaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		m_RendererID = program;
	}

    void OpenGLShader::CreateProgram(const ShaderSource &p_source)
    {
		GLuint program = glCreateProgram();

		std::vector<GLuint> shaderIDs;
		for (auto&& [stage, source] : p_source)
		{
			GLuint shaderID = shaderIDs.emplace_back(glCreateShader(ShaderTypeToOpenGL(stage)));
			auto source_char = source.c_str();
			glShaderSource(shaderID, 1, &source_char, NULL);
			glCompileShader(shaderID);
			int success = 0;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if(!success)
			{
				GLint maxLength;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> infoLog(maxLength);

				glGetShaderInfoLog(shaderID, maxLength, &maxLength, infoLog.data());
				std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog.data() << std::endl;
			};

			glAttachShader(program, shaderID);
		}

		glLinkProgram(program);

		GLint isLinked;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);

			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
			LERROR("Shader linking failed: {}", infoLog.data());

			for (auto id : shaderIDs)
				glDeleteShader(id);

			return;
		}

		for (auto id : shaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		m_RendererID = program;
    }

} // Lunib