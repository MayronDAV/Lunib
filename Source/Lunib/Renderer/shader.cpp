#include "shader.h"

#include "Lunib/Core/engine.h"
#include "Platform/OpenGL/opengl_shader.h"

// std
#include <fstream>
#include <iostream>
#include <filesystem>

// lib
#include <SPIRV/GlslangToSpv.h>
#include <glslang/Public/ShaderLang.h>



namespace Lunib
{
	static TBuiltInResource DefaultTBuiltInResource = {
		32,  // maxLights
		6,   // maxClipDistances
		8,   // maxCullDistances
		1,   // maxCombinedClipAndCullDistances
		2048, // maxCombinedShaderOutputResources
		4096, // maxComputeSharedMemorySize
		16,  // maxComputeWorkGroupCount
		1024, // maxComputeWorkGroupSize
		8,   // maxFragmentInputComponents
		64,  // maxImageUnits
		128, // maxImageSamples
		8,   // maxVertexOutputComponents
		8,   // maxTessControlOutputComponents
		16,  // maxTessEvaluationOutputComponents
		8,   // maxGeometryOutputComponents
		64,  // maxFragmentOutputAttachments
		8,   // maxGeometryInputComponents
		8,   // maxGeometryOutputComponents
		256, // maxFragmentCombinedOutputResources
		64,  // maxComputeWorkGroupInvocations
		16,  // maxWorkGroupSize
		1024, // maxWorkGroupCount
		8,   // maxGeometryOutputVertices
		1024, // maxGeometryTotalOutputComponents
		16,  // maxFragmentInputComponents
		16,  // maxVertexInputComponents
		1024, // maxTessControlInputComponents
		1024, // maxTessEvaluationInputComponents
		256, // maxTessControlOutputComponents
		1024, // maxTessEvaluationOutputComponents
		2048, // maxShaderStorageBufferBindings
		2048, // maxShaderStorageBufferSize
		128, // maxAtomicCounterBindings
		1024, // maxAtomicCounterBufferSize
		32,  // maxShaderImageSize
		2048, // maxShaderResourceSize
		64,  // maxShaderSamplerSize
		8,   // maxShaderConstantSize
		8,   // maxShaderPushConstantSize
		1024, // maxShaderUniformBufferSize
		128, // maxShaderStorageBufferSize
		1024, // maxShaderAtomicCounterSize
		256, // maxShaderAtomicCounterBindings
		2048, // maxShaderStorageBufferBindings
		256, // maxShaderStorageBufferSize
		2048, // maxShaderResourceSize
		128, // maxShaderSamplerSize
		128, // maxShaderSampledImageSize
		64,  // maxShaderImageSize
		8,   // maxShaderConstantSize
		16,  // maxShaderPushConstantSize
		256, // maxShaderUniformBufferSize
		2048, // maxShaderStorageBufferBindings
		256, // maxShaderStorageBufferSize
		2048, // maxShaderResourceSize
		128, // maxShaderSamplerSize
		128, // maxShaderSampledImageSize
		64,  // maxShaderImageSize
		8,   // maxShaderConstantSize
		16,  // maxShaderPushConstantSize
	};



	static std::string s_CacheDirectory = "cache/shader/";

	static ShaderType ShaderTypeFromString(const std::string& p_type)
	{
		if (p_type == "vertex")
			return ShaderType::Vertex;
		if (p_type == "fragment" || p_type == "pixel")
			return ShaderType::Fragment;

		return ShaderType(0);
	}

    static EShLanguage ShaderTypeToGlslang(ShaderType p_type)
    {
        switch (p_type)
        {
            case ShaderType::Vertex:   return EShLangVertex;
            case ShaderType::Fragment: return EShLangFragment;
            default:                   return EShLangCount;
        }
    }

	static std::vector<uint32_t> CompileGLSLToSPIRV(const std::string& source, ShaderType type)
    {
		glslang::InitializeProcess();

        EShLanguage stage = ShaderTypeToGlslang(type);
        glslang::TShader shader(stage);
        const char* shaderStrings[1];
        shaderStrings[0] = source.c_str();
        shader.setStrings(shaderStrings, 1);

		int ClientInputSemanticsVersion = 100;
		glslang::EShTargetClientVersion ClientVersion;
		glslang::EShTargetLanguageVersion TargetVersion;
		glslang::EShClient Client;
		if (Engine::GetAPI() == RenderAPI::OpenGL)
		{
			Client 			= glslang::EShClientOpenGL;
			ClientVersion 	= glslang::EShTargetOpenGL_450;
			TargetVersion 	= glslang::EShTargetSpv_1_6;
			shader.setAutoMapLocations(true);
			shader.setAutoMapBindings(true);
		}

		shader.setEnvInput(glslang::EShSourceGlsl, stage, Client, ClientInputSemanticsVersion);
		shader.setEnvClient(Client, ClientVersion);
		shader.setEnvTarget(glslang::EShTargetSpv, TargetVersion);

		TBuiltInResource Resources 					= DefaultTBuiltInResource;
		Resources.limits.generalUniformIndexing  	= true;
		Resources.limits.generalVariableIndexing 	= true;
		Resources.limits.nonInductiveForLoops	 	= true;

        if (auto rules = (EShMessages)(EShMsgSpvRules);
			!shader.parse(&Resources, 100, false, rules))
        {
			LERROR("GLSL parsing failed: {}", shader.getInfoLog());
            throw std::runtime_error("");
        }

        glslang::TProgram program;
        program.addShader(&shader);

        if (!program.link(EShMsgDefault))
        {
			LERROR("GLSL linking failed: {}", program.getInfoLog());
            throw std::runtime_error("");
        }

        std::vector<uint32_t> spirv;
        glslang::GlslangToSpv(*program.getIntermediate(stage), spirv);

		glslang::FinalizeProcess();
        return spirv;
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

	Shader* Shader::Create(const std::string& p_path, bool p_build_spirv /* = true */)
	{
		auto source	= Process(p_path);

		if (p_build_spirv)
			return Create(CompileOrGetSpirv(p_path, source, true));

		if (Engine::GetAPI() == RenderAPI::OpenGL)
			return new OpenGLShader(source);

		return nullptr;
	}

    Shader* Shader::Create(const std::string& p_name, const ShaderSource& p_source, bool p_build_spirv /* = false */)
    {
		if (p_build_spirv)
			return Create(CompileOrGetSpirv(p_name, p_source, false));

		if (Engine::GetAPI() == RenderAPI::OpenGL)
			return new OpenGLShader(p_source);

		return nullptr;
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
			LERROR("Could not open file: {}", p_path);
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

			assert((start != std::string::npos && end != std::string::npos) && "Invalid include directive!");
			assert((start < eol && end < eol) && "Not on the same line!");

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
			assert((eol != std::string::npos) && "Syntax error!\n");

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

		std::filesystem::path cacheDirectory = s_CacheDirectory;

		 std::unordered_map<ShaderType, std::vector<uint32_t>> spirv = {};
		for (auto&& [stage, source] : p_source)
		{
			std::filesystem::path cachedPath;
			if (p_isPath)
			{
				std::filesystem::path shaderFilePath = p_name;
				cachedPath = cacheDirectory / (shaderFilePath.stem().string() + ShaderTypeCachedFileExtension(stage));
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
				spirv[stage] = CompileGLSLToSPIRV(source, stage);

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

    Shader* ShaderLibrary::Get(const std::string& p_path, bool p_build_spirv /* = true */)
    {
		if (!Exists(p_path))
			s_Shaders[p_path].ptr = Shader::Create(p_path, p_build_spirv);

        return s_Shaders[p_path].ptr;
    }

    Shader* ShaderLibrary::Get(const std::string& p_name, const ShaderSource& p_source, bool p_build_spirv /* = false */)
    {
		if (!Exists(p_name))
			s_Shaders[p_name].ptr = Shader::Create(p_name, p_source, p_build_spirv);

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