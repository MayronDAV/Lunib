project "glslang"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/Thirdparty/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/Thirdparty/%{prj.name}")

	files
	{
		"include/glslang/ResourceLimits/**.cpp",
		"include/glslang/Public/**.h",
		"include/glslang/Public/**.cpp",
		"include/glslang/OSDependent/*.h",
		"include/glslang/MachineIndependent/**.h",
		"include/glslang/MachineIndependent/**.cpp",
		"include/glslang/Include/**.h",
		"include/glslang/GenericCodeGen/**.cpp",
		"include/glslang/ExtensionHeaders/*.glsl",
		"include/SPIRV/*.h",
		"include/SPIRV/*.cpp",
	}

	includedirs
	{
		"include"
	}

	filter "system:linux"
		systemversion "latest"

		files
		{
			"include/glslang/OSDependent/Unix/*.cpp"
		}

	filter "system:windows"
		systemversion "latest"

		files
		{
			"include/glslang/OSDependent/Windows/*.cpp"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
