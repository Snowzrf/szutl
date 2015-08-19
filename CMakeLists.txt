# CMake entry point
#
# This List was initially created using code both by Luke Iwanski
# and http://www.opengl-tutorial.org/
#
# Many thanks to Kenneth Benzie for the help!


# CMake setup
project (SnowzurferUtils)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/rpavlik-cmake-modules-1c73e35/")
cmake_minimum_required(VERSION 2.8.11.2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Setup handy variables:
set(SZUTL_EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)
set(SZUTL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SZUTL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(SZUTL_SCRIPTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake/scripts)


if(UNIX)
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # Color error output
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
  endif() # CMAKE_CXX_COMPILER_ID
endif() # UNIX

# Also add definitions for the compiler.
# If on Win32
if(WIN32)
	# Disables visual studio from treating warning as errors; this is necessary
	# because the compiler warns about code of the GLM library and would not
	# compile.
  add_definitions( "/W3 /WX- /D_CRT_SECURE_NO_WARNINGS /wd4005 /wd4996 /nologo" )
# If on linux
elseif(UNIX)
  #string(TOLOWER ${CMAKE_BUILD_TYPE} LOWER_BUILD_TYPE)
  if("${LOWER_BUILD_TYPE}" STREQUAL "DEBUG")
    # Add debug preprocessor macro
    add_definitions(-DICMP_DEBUG)
  endif() # TOLOWER
endif() # UNIX



# If on linux
if (UNIX)
  # Set the modules path
	set(CMAKE_MODULE_PATH /usr/local/lib/cmake /usr/local/lib/x86_64-linux-gnu/cmake)
	set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw)
endif() # UNIX



# Set platform-agnostic include dirs for the project
include_directories(
  ${SZUTL_INCLUDE_DIR}
)

# Set headers and sources for the szutl library
set(SZUTL_HEADERS
  ${SZUTL_INCLUDE_DIR}/szutl_binary_data_loader.h
)
set(SZUTL_SOURCES
  ${SZUTL_SOURCE_DIR}/szutl_binary_data_loader.cpp
)

# Create the szutl library
add_library(szutl ${SZUTL_HEADERS} ${SZUTL_SOURCES})


# Set the output directories for the user-defined libraries and binaries
set_target_properties (szutl
  PROPERTIES 
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")
