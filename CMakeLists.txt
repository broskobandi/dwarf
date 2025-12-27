cmake_minimum_required(FATAL_ERROR VERSION 3.30)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(GLOB MOD ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm)
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

if (UNIX AND NOT APPLE)
	message("[STATUS] Building on Linux.")

	# Use libc++
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

	# Ensure clang is being used
	if (NOT CMAKE_CXX_COMPILER)
		message(FATAL_ERROR "[ERROR] Please specify the c++ compiler.")
	endif()
	get_filename_component(COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)
	if (NOT COMPILER_NAME STREQUAL clang++)
		message(FATAL_ERROR
			"[ERROR] Must use clang++ as the project uses c++23 modules."
		)
	endif()
	message("[STATUS] Using ${COMPILER_NAME}")

	# Ensure Ninja is being used
	if (NOT CMAKE_GENERATOR STREQUAL Ninja)
		message(FATAL_ERROR
			"[ERROR] Must use Ninja as the project uses c++23 modules."
		)
	endif()
	message("[STATUS] Using Ninja.")

endif()

project(dwarf CXX C)

# Get sdl2-cppm
include(FetchContent)
FetchContent_Declare(
	sdl2-cppm
	GIT_REPOSITORY https://github.com/broskobandi/sdl2-cppm.git
	GIT_SHALLOW TRUE
	GIT_TAG main
)
FetchContent_MakeAvailable(sdl2-cppm)

# Add exe
add_executable(${PROJECT_NAME} ${SRC})
if (WIN32)
	add_dependencies(${PROJECT_NAME} sdl2-cppm-static sdl2-cppm SDL2)
endif()
add_dependencies(${PROJECT_NAME} sdl2-cppm-static sdl2-cppm)
target_link_libraries(${PROJECT_NAME} PRIVATE sdl2-cppm)
target_sources(
	${PROJECT_NAME} PRIVATE
	FILE_SET modules TYPE CXX_MODULES
	FILES ${MOD}
)

# Copy SDL library file to the target build dir
if (WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		$<TARGET_FILE:SDL2>
		$<TARGET_FILE_DIR:${PROJECT_NAME}>
	)
endif()
