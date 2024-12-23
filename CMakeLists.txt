cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(Lunib LANGUAGES C CXX)

if (POLICY CMP0069)
	cmake_policy(SET CMP0069 NEW)
endif()

if (POLICY CMP0077)
	cmake_policy(SET CMP0077 NEW)
endif()

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        ON)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if (CMAKE_BUILD_TYPE STREQUAL Debug AND WIN32)
	set(CMAKE_CXX_FLAGS_DEBUG "/Zi")
	set(CMAKE_LINKER_FLAGS_DEBUG "/DEBUG")
endif()

list(APPEND CMAKE_MODULE_PATH 	"${CMAKE_SOURCE_DIR}/CMake/modules/")
set(LIB_ROOT_DIR 				"${CMAKE_SOURCE_DIR}/Lib")

set(THIRDPARTY_DIR  			"${CMAKE_SOURCE_DIR}/Thirdparty")
set(SOURCE_DIR      			"${CMAKE_SOURCE_DIR}/Source")

file(GLOB_RECURSE SOURCE_FILES
								"${SOURCE_DIR}/**.h"
								"${SOURCE_DIR}/**.cpp"
)

set(LUNIB_DEFINITIONS 			"")
set(INCLUDE_FILES 	 			${SOURCE_DIR})
set(EXTERN_SRC_FILES 			"")
set(LIBS 						"")


# GLFW
add_subdirectory(${THIRDPARTY_DIR}/glfw)
list(APPEND LIBS 				glfw)
list(APPEND INCLUDE_FILES 		"${THIRDPARTY_DIR}/glfw/include")

# GLAD
list(APPEND EXTERN_SRC_FILES 	"${THIRDPARTY_DIR}/glad/src/glad.c")
list(APPEND INCLUDE_FILES 		"${THIRDPARTY_DIR}/glad/include")

# GLSLANG
set(BUILD_SHARED_LIBS 			OFF)
set(ENABLE_HLSL 				OFF)
set(ENABLE_SPVREMAPPER 			OFF)
set(ENABLE_GLSLANG_BINARIES 	OFF)
set(ENABLE_CTEST 				OFF)
set(ENABLE_OPT 					OFF)
set(ENABLE_VALIDATION 			OFF)
set(ENABLE_RTTI 				OFF)
set(ENABLE_EXCEPTIONS 			OFF)
add_subdirectory(${THIRDPARTY_DIR}/glslang)
list(APPEND LIBS 				glslang SPIRV)
list(APPEND INCLUDE_FILES 		"${THIRDPARTY_DIR}/glslang")



# FREETYPE
if(APPLE)
  	find_package(Freetype REQUIRED)
else()
	add_library(Freetype::Freetype UNKNOWN IMPORTED)
	set_target_properties(Freetype::Freetype PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES "${LIB_ROOT_DIR}/include/freetype"
	)
	set_property(TARGET Freetype::Freetype APPEND PROPERTY
		IMPORTED_CONFIGURATIONS RELEASE
	)
	set_target_properties(Freetype::Freetype PROPERTIES
		IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
		IMPORTED_LOCATION_RELEASE "${LIB_ROOT_DIR}/freetype.lib"
	)
	#list(APPEND INCLUDE_FILES 	  "${LIB_ROOT_DIR}/include/freetype")
endif()

# MSDF
set(MSDF_ATLAS_BUILD_STANDALONE OFF)
set(MSDF_ATLAS_USE_VCPKG 		OFF)
set(MSDF_ATLAS_USE_SKIA 		OFF)
set(MSDFGEN_DISABLE_PNG 		TRUE) # TODO
add_subdirectory(${THIRDPARTY_DIR}/msdf-atlas-gen)
list(APPEND LIBS 				msdf-atlas-gen)
list(APPEND INCLUDE_FILES 		"${THIRDPARTY_DIR}/msdf-atlas-gen/msdf-atlas-gen")
list(APPEND INCLUDE_FILES 		"${THIRDPARTY_DIR}/msdf-atlas-gen/msdfgen")

# STB
list(APPEND INCLUDE_FILES 		"${THIRDPARTY_DIR}/stb/include")


if(WIN32)
	list(APPEND LUNIB_DEFINITIONS "LUNIB_WINDOWS")
	list(APPEND LIBS opengl32)
  	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif(UNIX AND NOT APPLE)
	list(APPEND LUNIB_DEFINITIONS "LUNIB_LINUX")
	set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
	find_package(OpenGL REQUIRED)
	# add_definitions(${OPENGL_DEFINITIONS})
	list(APPEND LUNIB_DEFINITIONS ${OPENGL_DEFINITIONS})
	find_package(X11 REQUIRED)
	list(APPEND LIBS X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread)
	set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
elseif(APPLE)
	list(APPEND LUNIB_DEFINITIONS "LUNIB_APPLE")
	# include_directories(/System/Library/Frameworks)
	set(FIND_PATH "/System/Library/Frameworks")
	find_library(COCOA_LIBRARY Cocoa PATHS FIND_PATH)
	find_library(OpenGL_LIBRARY OpenGL PATHS FIND_PATH)
	find_library(IOKit_LIBRARY IOKit PATHS FIND_PATH)
	find_library(CoreVideo_LIBRARY CoreVideo PATHS FIND_PATH)
	mark_as_advanced(COCOA_LIBRARY OpenGL_LIBRARY)
	set(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY} ${CoreVideo_LIBRARY})
	list(APPEND LIBS ${APPLE_LIBS})
endif()

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${EXTERN_SRC_FILES})

target_compile_definitions(${PROJECT_NAME} PUBLIC 
							$<$<CONFIG:Debug>:LUNIB_DEBUG> 
							$<$<CONFIG:Release>:LUNIB_RELEASE> 
							"LUNIB_EXPORT" ${LUNIB_DEFINITIONS})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE /std:c++20 /MP)
	target_link_options(${PROJECT_NAME} PUBLIC /ignore:4099)
endif()

set(OUTPUT_BASE_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME})

function(set_output_dir base_dir target)
	set_target_properties(${target} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${base_dir}/$<CONFIG>/${target}
		LIBRARY_OUTPUT_DIRECTORY ${base_dir}/$<CONFIG>/${target}
	)

	if(MSVC OR APPLE)
		set_target_properties(${target} PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY_DEBUG  	${base_dir}/$<CONFIG>/${target}
			RUNTIME_OUTPUT_DIRECTORY_RELEASE  	${base_dir}/$<CONFIG>/${target}
			LIBRARY_OUTPUT_DIRECTORY_DEBUG  	${base_dir}/$<CONFIG>/${target}
			LIBRARY_OUTPUT_DIRECTORY_RELEASE  	${base_dir}/$<CONFIG>/${target}
		)
	endif()

	if(WIN32)
		set_target_properties(${target} PROPERTIES
		 	VS_DEBUGGER_WORKING_DIRECTORY ${base_dir}/$<CONFIG>/${target}
		)
	endif()

endfunction()

set_output_dir(${OUTPUT_BASE_DIR} ${PROJECT_NAME})


function(copy_file src dest target)
    if(WIN32)
        add_custom_command(
            TARGET ${target} 
            PRE_BUILD 
            COMMAND ${CMAKE_COMMAND} -E copy ${src} ${dest} 
            COMMENT "Copying file: ${src} -> ${dest}"
        )
    elseif(UNIX AND NOT APPLE)
        add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${src} ${dest}
            COMMENT "Copying file (Unix): ${src} -> ${dest}"
        )
    elseif(APPLE)
		add_custom_command(
			TARGET ${target} 
			POST_BUILD 
			COMMAND ${CMAKE_COMMAND} -E create_symlink ${src} ${dest}  
			COMMENT "Creating symbolic link: ${src} -> ${dest}"
		)
    endif()
endfunction()


set(MASTER_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  	set(MASTER_PROJECT ON)
endif()

option(LUNIB_BUILD_SANDBOX "Build sandbox" ${MASTER_PROJECT})

if (LUNIB_BUILD_SANDBOX)
	add_subdirectory(Sandbox)
endif()