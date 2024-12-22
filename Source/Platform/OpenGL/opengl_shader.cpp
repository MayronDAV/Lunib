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

	void OpenGLShader::PushValue(const std::string& p_name, void* p_value)
	{
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
			std::cout << "Shader linking failed: " << infoLog.data() << "\n";

			for (auto id : shaderIDs)
				glDeleteShader(id);

		}

		for (auto id : shaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		m_RendererID = program;
	}

} // Lunib