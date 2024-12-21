cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(Sandbox LANGUAGES C CXX)

file(GLOB_RECURSE SANDBOX_SRC_FILES 
					"${CMAKE_CURRENT_SOURCE_DIR}/Source/**.h"
					"${CMAKE_CURRENT_SOURCE_DIR}/Source/**.cpp"
)

add_executable(${PROJECT_NAME} ${SANDBOX_SRC_FILES})

copy_file($<TARGET_FILE:Lunib> ${OUTPUT_BASE_DIR}/$<CONFIG>/${PROJECT_NAME} ${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PUBLIC 
							$<$<CONFIG:Debug>:LUNIB_DEBUG> 
							$<$<CONFIG:Release>:LUNIB_RELEASE> 
							${LUNIB_DEFINITIONS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Source)

target_link_libraries(${PROJECT_NAME} Lunib)

set_output_dir(${OUTPUT_BASE_DIR} ${PROJECT_NAME})