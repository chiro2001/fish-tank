cmake_minimum_required(VERSION 3.0.0)
project(fish-tank-server VERSION 0.2)

include(CTest)
enable_testing()

message(STATUS "${PROJECT_NAME} started building on ${CMAKE_SYSTEM_NAME}!")

# Include
set(include_dirs
    "${PROJECT_SOURCE_DIR}/tests/flv")
message(STATUS "Include dirs: ${include_dirs}")
include_directories(${include_dirs})

# Src

file(GLOB_RECURSE source_files
        "${PROJECT_SOURCE_DIR}/tests/flv/*.h"
        "${PROJECT_SOURCE_DIR}/tests/flv/amf.c"
        "${PROJECT_SOURCE_DIR}/tests/flv/flv*.c"
        "${PROJECT_SOURCE_DIR}/tests/flv/types.c"
)
message(STATUS "Source files: ${source_files}")

# Resources
file(GLOB_RECURSE resources "${PROJECT_SOURCE_DIR}/resource/*")
message(STATUS "Copying resources file(s): ${resources}")
file(COPY ${resources} DESTINATION ${CMAKE_BINARY_DIR}/)

# Linking

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -DHAVE_CONFIG_H")

add_executable(flv-test ${PROJECT_SOURCE_DIR}/tests/flv/test.c ${source_files})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
