cmake_minimum_required(VERSION 3.14)
# Project Details
set(PROJECT_NAME "CPPLib")
set(PROJECT_VERSION 0.0.1)
set(PROJECT_EMAIL   "")
set(PROJECT_HOME    "")
set(PROJECT_DOCS    "")
set(PROJECT_CODE    "")
set(PROJECT_ISSUES  "")
set(PYPI_PACKAGE_NAME "cpplib")
# Set Project Properties
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION}
DESCRIPTION "C++ and Python Skeleton for Libraries"
LANGUAGES CXX)
# Set Global Properties
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Release)
endif()

# Include CMAKE folder
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Extras.cmake)

# Output Folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Build Options
option(WERROR "Add -Werror flag to build (turns warnings into errors)" OFF)
option(WITH_PROFILE "Enable Profiling" ON)

# Options for CPPL
option(CPPL_BUILD_PYMODULE "CPPL -Build Python Module" ON)
option(CPPL_BUILD_TESTS "CPPL - Build Tests" ON)
option(CPPL_BUILD_BENCHMARKS "CPPL - Build Benchmarks" ON)
option(CPPL_BUILD_EXAMPLES "CPPL - Build Examples" ON)

# Configure optimization
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OPTIMIZATION_FLAGS "-O0 -DDEBUG")
    message("-- Configuring debug build")
else()
    set(OPTIMIZATION_FLAGS "-O3 -DNDEBUG")
    message("-- Configuring release build")
endif()

# Enable warnings, will set to compile with src/CMakeLists.txt
set(DESIRED_WARNINGS "-Wall -Wextra -Wconversion -Wunreachable-code -Wuninitialized -pedantic-errors -Wold-style-cast -Wno-error=unused-variable -Wshadow -Wfloat-equal -Weffc++")
set(MINIMAL_DESIRED_WARNINGS "-Wall -Wextra -pedantic-errors")
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(DESIRED_WARNINGS "${DESIRED_WARNINGS} -Wmost")
endif()
separate_arguments(DESIRED_WARNINGS)
separate_arguments(MINIMAL_DESIRED_WARNINGS)

### Set GLOBAL CMAKE_CXX_FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS}")
if (WERROR)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

# always build src
add_subdirectory("src")

# Build examples if configured
if(CPPL_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

# Build tests if configured
if(CPPL_BUILD_TESTS)
    add_subdirectory("tests")
endif()

# Build benchmarks if configured
if(CPPL_BUILD_BENCHMARKS)
    add_subdirectory("bench")
endif()


