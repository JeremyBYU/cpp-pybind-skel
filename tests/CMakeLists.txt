include(FetchContent)
FetchContent_Declare(
  extern_doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_TAG        2.3.7
)

# This module depend on having googletest installed
FetchContent_MakeAvailable(extern_doctest)

