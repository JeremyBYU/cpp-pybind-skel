############ Start Version Parsing ##################

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/version.txt" CPPLIB_VERSION_READ)
foreach(ver ${CPPLIB_VERSION_READ})
    if (ver MATCHES "(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(CPPLIB_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
string(CONCAT CPPLIB_VERSION
    "${CPPLIB_VERSION_MAJOR}"
    ".${CPPLIB_VERSION_MINOR}"
    ".${CPPLIB_VERSION_PATCH}"
)

set(PROJECT_VERSION "${CPPLIB_VERSION}")

message("Version is ${PROJECT_VERSION}")

############# End Version Parsing ##################


add_subdirectory(CPPLib)

if (CPPL_BUILD_PYMODULE)
    add_subdirectory(Python)
endif ()
