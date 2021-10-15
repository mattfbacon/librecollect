cmake_minimum_required(VERSION 3.21)

set(EXECUTABLE_NAME recollect)
set(PROJECT_NAME Recollect)

# Dirs
set(DIR_SRC src)
set(DIR_DIST dist)
set(DIR_INCLUDE include)
set(DIR_SYSINC sysinc)
set(DIR_LIB lib)

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES C CXX)

# Sources
set (sources
	ConnectionMeans.cpp
	get.cpp
	lifetime.cpp
	set.cpp
	clear.cpp
	delete.cpp
	has.cpp
	numeric.cpp
	insertion.cpp
	behavior.cpp
	flush.cpp
	)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_POSITION_INDEPENDENT_CODE True)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

# Linker/Compiler Flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
	-fuse-ld=lld \
	")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
	-Wall -Wextra -Wno-unknown-pragmas \
	-Wcpp \
	-Wno-enum-compare \
	-frtti -fexceptions \
	-DMSGPACK_DISABLE_LEGACY_CONVERT \
	")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto -fcolor-diagnostics \
		-Wno-gnu-zero-variadic-macro-arguments \
		-Wno-c++11-extensions -Wno-c++14-extensions \
		-Wno-c++17-extensions -Wno-c++20-extensions \
		-Wno-unused-command-line-argument \
		")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
	-fno-omit-frame-pointer -fstack-protector-strong \
	-Og -ggdb3 -Werror -Wfatal-errors -Wno-error=cpp -Wno-error=pedantic \
	")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} \
	-DNDEBUG \
	")

option(USE_ASAN "Use Address Sanitizer (Debug Only)" ON)
if(${USE_ASAN})
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
		-finstrument-functions \
		-fsanitize=address -fsanitize=undefined -fsanitize=leak \
		")
endif()

option(USE_GLIBCXX_DEBUG "STL Debug Mode (Debug Only)" ON)
if(${USE_GLIBCXX_DEBUG})
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
		-D_GLIBCXX_DEBUG \
		")
endif()

list(TRANSFORM sources PREPEND ${${PROJECT_NAME}_SOURCE_DIR}/${DIR_SRC}/)

add_library(${EXECUTABLE_NAME} SHARED ${sources})
target_include_directories(${EXECUTABLE_NAME} PUBLIC ${${PROJECT_NAME}_SOURCE_DIR}/${DIR_INCLUDE})
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${${PROJECT_NAME}_SOURCE_DIR}/${DIR_INCLUDE}/${EXECUTABLE_NAME})

set_property(TARGET ${EXECUTABLE_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY "${${PROJECT_NAME}_SOURCE_DIR}/${DIR_DIST}")
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY LIBRARY_OUTPUT_DIRECTORY "${${PROJECT_NAME}_SOURCE_DIR}/${DIR_DIST}")
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY ARCHIVE_OUTPUT_DIRECTORY "${${PROJECT_NAME}_SOURCE_DIR}/${DIR_DIST}")

include(test.cmake)

# Extra Stuff Starts Here
target_link_libraries(${EXECUTABLE_NAME} PRIVATE memcached)
