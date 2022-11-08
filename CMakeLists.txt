cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_TOOLCHAIN_FILE "")

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})

project(SECOND_PROGRAMMING_PRACTICE VERSION ${PROJECT_VERSION})

include(CTest)
enable_testing()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

message("Project version: ${PROJECT_VERSION}")
message("Toolchain status: ${CMAKE_TOOLCHAIN_FILE}")
message("Cmake include current directory: ${CMAKE_INCLUDE_CURRENT_DIR}")
#message("CTest status: ${CPACK_PROJECT_NAME} version ${CPACK_PROJECT_VERSION};")

# CHECK IF SYSTEMS IS RUNNING WINDOWS AND ADD NECESSARY ATTRIBUTES.
if(WIN32)
        # ADD SOURCE FILES
        file(GLOB_RECURSE TASK_1_CPP
                                        "${PROJECT_SOURCE_DIR}/task_1/source/*.cpp"
        )
        file(GLOB_RECURSE TASK_1_H
                                        "${PROJECT_SOURCE_DIR}/task_1/source/*.h"
        )

        message("Source files for \"Task 1\" added")

        add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/DURLIB")

        add_executable(TASK_1 
        #WIN32
                                        "${PROJECT_SOURCE_DIR}/task_1/main.cpp"
                                        ${TASK_1_CPP}
        )

        target_include_directories(TASK_1 PUBLIC
                                        #"${LOUNGE_H}"
                                        "${PROJECT_SOURCE_DIR}/task_1/source"
        )

        # target_precompile_headers(LOUNGE PUBLIC
        #                                 "${PROJECT_SOURCE_DIR}/lounge/source/PCH.h"
        # )

        target_link_libraries(TASK_1 PUBLIC
                                        durlib
        )

        message("Executable added")

        # COMPILER DEFINITIONS.
        target_compile_definitions(TASK_1 PUBLIC CLI_PLATFORM_WINDOWS)
        target_compile_definitions(TASK_1 PUBLIC CLI_STATIC_LIBRARY)
        target_compile_definitions(TASK_1 PUBLIC CLI_ENABLE_ASSERTS)

        # ENABLE PROFILING FOR DEBUG BUILS.
        if(CMAKE_BUILD_TYPE STREQUAL Debug)
                target_compile_definitions(TASK_1 PUBLIC CLI_DEBUG_PROFILING)
        endif(CMAKE_BUILD_TYPE STREQUAL Debug)

endif (WIN32)

# DOUBLE CHECKS IF THE SYSTEM IS RUNNING ON WINDOWS-X64 SYSTEM.
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)

        message("PROJECT SUPPORTS ONLY X64 SYSTEMS.")
        return()

endif()