#pragma once
#include "Lunib/Core/base.h"
#include "Lunib/Math/Ext/vector.h"
#include "Lunib/Core/definitions.h"

// std
#include <string>
#include <unordered_map>
#include <vector>




namespace Lunib
{
	using ShaderSource = std::unordered_map<ShaderType, std::string>;

	class LUNIB_API Shader
	{
		friend class ShaderLibrary;
			 
		public:
			virtual ~Shader() = default;

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual void PushValue(const std::string& p_name, void* p_value) = 0;

		protected:
			Shader() = default;

			static Shader* Create(const std::string& p_path);
			static Shader* Create(const std::string& p_name, const ShaderSource& p_source);
			static Shader* Create(const std::unordered_map<ShaderType, std::vector<uint32_t>>& p_spirv);

		private:
			static std::string ReadFile(const std::string& p_path);
			static std::string ProcessIncludeFiles(const std::string& p_path, const std::string& p_code);
			static ShaderSource Process(const std::string& p_path);

			static std::unordered_map<ShaderType, std::vector<uint32_t>> CompileOrGetSpirv(const std::string& p_name, const ShaderSource& p_source, bool p_isPath);
	};



	class LUNIB_API ShaderLibrary
	{
		public:
			static void Release();

			static Shader* Get(const std::string& p_path);
			static Shader* Get(const std::string& p_name, const ShaderSource& p_source);

			static void SetCacheDirectory(const std::string& p_path);

			static bool Exists(const std::string& p_key);
	};
}
