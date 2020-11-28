include(FetchContent)
# Put any LIBRARY dependencies in here
FetchContent_Declare(
  extern_pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v2.6.1
)

# After the following call, the pybind11 library will be installed
FetchContent_MakeAvailable(extern_pybind11)

# Nanobench and docttest will only be downloaded & installed if configured to do so with CMake Options
# This download occurs, with FetchContent_MakeAvailable call, in the "bench" and "tests" directory