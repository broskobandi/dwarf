cmake_minimum_required(FATAL_ERROR VERSION 3.30)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(GLOB MOD src/*.cppm)
file(GLOB SRC src/*.cpp)

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

	# Ensure std.cppm is available
	if (NOT STD_CPPM)
		message(FATAL_ERROR
			"[ERROR] Please provide path to std.cppm with: -DSTD_CPPM=/path/to/std.cppm"
		)
	endif()
	file(GLOB STD ${STD_CPPM})
	if (NOT STD)
		message(FATAL_ERROR
			"[ERROR] std.cppm not found."
		)
	endif()
	set(MOD ${MOD} STD)
	message("[STATUS] std.cppm found.")


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
target_link_libraries(${PROJECT_NAME} PRIVATE sdl2-cppm)

if (WIN32)
endif()
