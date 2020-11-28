include(FetchContent)
# Put any LIBRARY dependencies in here
FetchContent_Declare(
  extern_pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v2.6.1
)

FetchContent_Declare(
  extern_nanobench
  GIT_REPOSITORY https://github.com/martinus/nanobench.git
  GIT_TAG v4.1.0
  GIT_SHALLOW TRUE
)

FetchContent_Declare(
  extern_doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_TAG        2.3.7
)


# After the following call, the pybind11 library will be installed
FetchContent_MakeAvailable(extern_pybind11)

# Nanobench and docttest will only be downloaded & installed if configured to do so with CMake Options
# This download occurs, with FetchContent_MakeAvailable call, in the "bench" and "tests" directory