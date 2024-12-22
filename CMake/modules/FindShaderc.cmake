set( SHADERC_HEADER_FIND_ARGS
	"/usr/include"
	"/usr/local/include"
	"${CMAKE_SOURCE_DIR}/Lib/include"
)

set( SHADERC_LIB_FIND_ARGS
	"/usr/lib"
	"/usr/local/lib"
	"${CMAKE_SOURCE_DIR}/Lib"
)

set(VULKAN_SDK_PATH "$ENV{VULKAN_SDK}")

if( VULKAN_SDK_PATH )
	list( INSERT SHADERC_HEADER_FIND_ARGS 0 "${VULKAN_SDK_PATH}/Include" )
	list( INSERT SHADERC_LIB_FIND_ARGS 	  0 "${VULKAN_SDK_PATH}/Lib" 	 )
endif()

# Search for the header
find_path(
	SHADERC_INCLUDE_DIR 
	NAMES
		shaderc/shaderc.h
		shaderc.h
	PATHS 
		${SHADERC_HEADER_FIND_ARGS} 
	PATH_SUFFIXES
		shaderc
)

# Search for the library
find_library(
	SHADERC_LIBRARY
	NAMES 
		shaderc_shared
		shaderc
	PATHS 
		${SHADERC_LIB_FIND_ARGS}
	PATH_SUFFIXES
		Lib
)

# if (VULKAN_SDK_PATH)
# 	set(SHADERC_INCLUDE_DIR ${SHADERC_INCLUDE_DIR}/shaderc)
# endif()

unset(SHADERC_HEADER_FIND_ARGS)
unset(SHADERC_LIB_FIND_ARGS)
unset(VULKAN_SDK_PATH)


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
 	Shaderc
  	REQUIRED_VARS
  		SHADERC_LIBRARY
		SHADERC_INCLUDE_DIR
)

if(Shaderc_FOUND)
	if (NOT TARGET Shaderc::Shaderc)
		add_library(Shaderc::Shaderc UNKNOWN IMPORTED)
		set_target_properties(Shaderc::Shaderc PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${SHADERC_INCLUDE_DIR}"
		)

		if(SHADERC_LIBRARY)
			set_property(TARGET Shaderc::Shaderc APPEND PROPERTY
			IMPORTED_CONFIGURATIONS RELEASE)
			set_target_properties(Shaderc::Shaderc PROPERTIES
			IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
			IMPORTED_LOCATION_RELEASE "${SHADERC_LIBRARY}")
		endif()

	endif()

	if (TARGET Shaderc::Shaderc)
		add_library(Shaderc ALIAS Shaderc::Shaderc)
	endif()
endif()
