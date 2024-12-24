#pragma once
#include "Lunib/Core/base.h"
#include "Lunib/Math/Ext/vector.h"
#include "Lunib/Math/math.h"
#include "Lunib/Core/definitions.h"

// std
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>




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

			virtual void SetInt(const std::string& p_name, int p_value) = 0;
			virtual void SetMat4(const std::string& p_name, const Mat4& p_value) = 0;
			virtual void SetMat3(const std::string& p_name, const Mat3& p_value) = 0;
			virtual void SetVec2(const std::string& p_name, const Vec2& p_value) = 0;
			virtual void SetVec3(const std::string& p_name, const Vec3& p_value) = 0;
			virtual void SetVec4(const std::string& p_name, const Vec4& p_value) = 0;


		protected:
			Shader() = default;

			static Shader* Create(const std::string& p_path, bool p_build_spirv = true);
			static Shader* Create(const std::string& p_name, const ShaderSource& p_source, bool p_build_spirv = false);
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

			static Shader* Get(const std::string& p_path, bool p_build_spirv = true);
			static Shader* Get(const std::string& p_name, const ShaderSource& p_source, bool p_build_spirv = false);

			static Shader* Reload(const std::string& p_path, bool p_build_spirv = true);
			static Shader* Reload(const std::string& p_name, const ShaderSource& p_source, bool p_build_spirv = false);

			static void SetCacheDirectory(const std::string& p_path);

			static bool Exists(const std::string& p_key);
	};
}
