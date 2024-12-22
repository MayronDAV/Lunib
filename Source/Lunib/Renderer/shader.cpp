#include "shader.h"

#include "Lunib/Core/engine.h"
#include "Platform/OpenGL/opengl_shader.h"

// std
#include <fstream>
#include <iostream>
#include <filesystem>

// lib
#include <shaderc/shaderc.hpp>



namespace Lunib
{
	static std::string s_CacheDirectory = "cache/shader/";

	static ShaderType ShaderTypeFromString(const std::string& p_type)
	{
		if (p_type == "vertex")
			return ShaderType::Vertex;
		if (p_type == "fragment" || p_type == "pixel")
			return ShaderType::Fragment;

		return ShaderType(0);
	}

	static shaderc_shader_kind ShaderTypeToShaderc(ShaderType p_type)
	{
		switch (p_type)
		{
			case ShaderType::Vertex:   return shaderc_glsl_vertex_shader;
			case ShaderType::Fragment: return shaderc_glsl_fragment_shader;
		}

		return (shaderc_shader_kind)0;
	}

	static void CreateDirectoryIfNeeded(const std::string& p_path)
	{
		if (!std::filesystem::exists(p_path))
			std::filesystem::create_directories(p_path);
	}

	static const char* ShaderTypeCachedFileExtension(ShaderType p_type)
	{
		switch (p_type)
		{
			case ShaderType::Vertex:    return ".cached.vert";
			case ShaderType::Fragment:  return ".cached.frag";
		}

		return "";
	}

	Shader* Shader::Create(const std::string& p_path)
	{
		auto shaderSource 	= Process(p_path);

		return Create(CompileOrGetSpirv(p_path, shaderSource, true));
	}

    Shader* Shader::Create(const std::string& p_name, const ShaderSource& p_source)
    {
		return Create(CompileOrGetSpirv(p_name, p_source, false));
    }

    Shader* Shader::Create(const std::unordered_map<ShaderType, std::vector<uint32_t>>& p_spirv)
    {
        if (Engine::GetAPI() == RenderAPI::OpenGL)
			return new OpenGLShader(p_spirv);

		return nullptr;
    }

    std::string Shader::ReadFile(const std::string& p_path)
    {
        std::string result;
		std::ifstream shaderFile{ p_path.data(), std::ios::in | std::ios::binary};

		if (!shaderFile)
		{
			std::cerr << "Could not open file: " << p_path << "\n";
			return std::string();
		}

		shaderFile.seekg(0, std::ios::end);
		result.resize(shaderFile.tellg());
		shaderFile.seekg(0, std::ios::beg);

		shaderFile.read(&result[0], result.size());
		shaderFile.close();

		return result;
    }

    std::string Shader::ProcessIncludeFiles(const std::string& p_path, const std::string& p_code)
    {
		auto result = std::string();

		const char* includeToken = "#include";
		size_t pos = p_code.find(includeToken, 0);
		if (pos == std::string::npos)
		{
			return p_code;
		}

		while (pos != std::string::npos)
		{
			if (result == std::string())
			{
				result = p_code.substr(0, pos);
			}
			
			size_t eol = p_code.find_first_of("\r\n", pos);
			size_t start = p_code.find("<", pos);
			size_t end = p_code.find(">", start);

			if (start == std::string::npos)
			{
				start = p_code.find("\"", pos);
				end   = p_code.find("\"", start);
			}

			if (!(start != std::string::npos && end != std::string::npos))
			{
				std::cerr << "Invalid include directive!\n";
				return p_code;
			}

			if (!(start < eol && end < eol))
			{
				std::cerr << "Not on the same line!\n";
				return p_code;
			}

			std::string includeFilepath = p_code.substr(start + 1, end - start - 1);
			std::filesystem::path filepath = p_path;
			auto path = (filepath.parent_path() / includeFilepath).string();
			std::string includeCode = ReadFile(path);

			result += includeCode;

			pos = p_code.find(includeToken, end + 1);
			if (pos == std::string::npos)
			{
				result += p_code.substr(end + 1);
			}
			else
			{
				result += p_code.substr(end + 1, pos - end - 1);
			}
		}

		return result;
    }

    ShaderSource Shader::Process(const std::string& p_path)
    {
		ShaderSource shaderSources;

		auto source = ReadFile(p_path);

		const char* typeToken = "@type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			if (!(eol != std::string::npos))
			{
				std::cerr << "Syntax error!\n";
				return ShaderSource();
			}

			size_t begin = source.find_first_not_of(" \t", pos + typeTokenLength);
			size_t end = source.find_last_not_of(" \t", eol);
			std::string type = source.substr(begin, end - begin + 1);
			if (size_t typeEnd = type.find_first_of(" \r\n");
				typeEnd != std::string::npos) {
				type.erase(typeEnd);
			}

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			auto code = source.substr(
				nextLinePos,
				pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos)
			);
			auto newCode = ProcessIncludeFiles(p_path, code);
			shaderSources[ShaderTypeFromString(type)] = newCode;
		}

		return shaderSources;
    }

    std::unordered_map<ShaderType, std::vector<uint32_t>> Shader::CompileOrGetSpirv(const std::string& p_name, const ShaderSource &p_source, bool p_isPath)
    {
		CreateDirectoryIfNeeded(s_CacheDirectory);

		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		bool optimize = true;
		if (Engine::GetAPI() == RenderAPI::OpenGL)
		{
			options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
			optimize = false;
		}

		if (optimize)
			options.SetOptimizationLevel(shaderc_optimization_level_performance);

		std::filesystem::path cacheDirectory = s_CacheDirectory;

		 std::unordered_map<ShaderType, std::vector<uint32_t>> spirv = {};
		for (auto&& [stage, source] : p_source)
		{
			std::filesystem::path cachedPath;
			if (p_isPath)
			{
				std::filesystem::path shaderFilePath = p_name;
				cachedPath = cacheDirectory / (shaderFilePath.filename().string() + ShaderTypeCachedFileExtension(stage));
			}
			else
			{
				cachedPath = cacheDirectory / (p_name + ShaderTypeCachedFileExtension(stage));
			}

			std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
			if (in.is_open())
			{
				in.seekg(0, std::ios::end);
				auto size = in.tellg();
				in.seekg(0, std::ios::beg);

				auto& data = spirv[stage];
				data.resize(size / sizeof(uint32_t));
				in.read((char*)data.data(), size);
			}
			else
			{
				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, ShaderTypeToShaderc(stage), p_name.c_str(), options);
				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					std::cerr << module.GetErrorMessage() << "\n";
					return {};
				}

				spirv[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());

				std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
				if (out.is_open())
				{
					auto& data = spirv[stage];
					out.write((char*)data.data(), data.size() * sizeof(uint32_t));
					out.flush();
					out.close();
				}
			}
		}

		return spirv;
    }

    // ShaderLibrary
	// =================================================================================================

	struct ShaderAsset
	{
		Shader* ptr;
	};
	static std::unordered_map<std::string, ShaderAsset> s_Shaders;

	void ShaderLibrary::Release()
	{
		for (auto& shader : s_Shaders)
			delete shader.second.ptr;

		s_Shaders.clear();
	}

    Shader* ShaderLibrary::Get(const std::string& p_path)
    {
		if (!Exists(p_path))
			s_Shaders[p_path].ptr = Shader::Create(p_path);

        return s_Shaders[p_path].ptr;
    }

    Shader* ShaderLibrary::Get(const std::string& p_name, const ShaderSource& p_source)
    {
		if (!Exists(p_name))
			s_Shaders[p_name].ptr = Shader::Create(p_name, p_source);

        return s_Shaders[p_name].ptr;
    }

    void ShaderLibrary::SetCacheDirectory(const std::string &p_path)
    {
		s_CacheDirectory = p_path;
    }

    bool ShaderLibrary::Exists(const std::string& p_key)
    {
		auto it = s_Shaders.find(p_key);
		return it != s_Shaders.end();
    }

} // Lunib