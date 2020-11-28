include(FetchContent)
# This module depend on having doctest installed
FetchContent_Declare(
  extern_doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_TAG        2.3.7
)

FetchContent_MakeAvailable(extern_doctest)

add_executable(run-tests ${CMAKE_CURRENT_SOURCE_DIR}/run-tests.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test-cpplib.cpp)
target_link_libraries(run-tests PRIVATE doctest::doctest CPPLib::CPPL)

