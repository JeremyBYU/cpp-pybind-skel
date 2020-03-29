include(FetchContent)

FetchContent_Declare(
  extern_googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.5.0
)

# This module depend on having googletest and googlebenchmark installed
FetchContent_GetProperties(extern_googlebenchmark)
if(NOT extern_googlebenchmark_POPULATED)
  FetchContent_Populate(extern_googlebenchmark)
  SET(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Enable testing of the benchmark library.")
  add_subdirectory(${extern_googlebenchmark_SOURCE_DIR} ${extern_googlebenchmark_BINARY_DIR})
endif()




