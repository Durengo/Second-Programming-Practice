cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_TOOLCHAIN_FILE "")

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 5)
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

set(T1 ON)
set(T2 ON)

# message("CTest status: ${CPACK_PROJECT_NAME} version ${CPACK_PROJECT_VERSION};")

# CHECK IF SYSTEMS IS RUNNING WINDOWS AND ADD NECESSARY ATTRIBUTES.
if(WIN32)
        add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/durlib")

        if(T1)
                # ADD SOURCE FILES
                file(GLOB_RECURSE TASK_1_CPP
                        "${PROJECT_SOURCE_DIR}/task_1/source/*.cpp"
                )
                file(GLOB_RECURSE TASK_1_H
                        "${PROJECT_SOURCE_DIR}/task_1/source/*.h"
                )

                message("Source files for \"Task 1\" added")

                add_executable(TASK_1
                        "${PROJECT_SOURCE_DIR}/task_1/main.cpp"

                        # ${TASK_1_CPP}
                )

                # target_include_directories(TASK_1 PUBLIC
                # "${PROJECT_SOURCE_DIR}/task_1/source"
                # )
                target_link_libraries(TASK_1 PUBLIC
                        DURLIB
                )

                message("TASK_1 Executable added")
        endif()

        if(T2)
                # ADD SOURCE FILES
                file(GLOB_RECURSE TASK_2_CPP

                        "${PROJECT_SOURCE_DIR}/task_2/source/Airplane/*.cpp"

                        "${PROJECT_SOURCE_DIR}/task_2/source/Passenger/*.cpp"

                        "${PROJECT_SOURCE_DIR}/task_2/source/Airport/*.cpp"

                        "${PROJECT_SOURCE_DIR}/task_2/source/AirportSimulation.cpp"
                )
                file(GLOB_RECURSE TASK_2_H

                        "${PROJECT_SOURCE_DIR}/task_2/source/Airplane/*.h"

                        "${PROJECT_SOURCE_DIR}/task_2/source/Passenger/*.h"

                        "${PROJECT_SOURCE_DIR}/task_2/source/Airport/*.h"

                        "${PROJECT_SOURCE_DIR}/task_2/source/AirportSimulation.h"
                )

                message("Source files for \"Task 2\" added")

                add_executable(TASK_2
                        "${PROJECT_SOURCE_DIR}/task_2/main.cpp"
                        ${TASK_2_CPP}
                )

                if(MSVC)
                        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
                endif()

                # find_path(FAST_CPP_CSV_PARSER_INCLUDE_DIRS "csv.h")
                target_include_directories(TASK_2 PUBLIC
                        "${PROJECT_SOURCE_DIR}/task_2/source"
                        "${PROJECT_SOURCE_DIR}/vendor/fast-cpp-csv-parser"

                        # ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS}
                )

                target_link_libraries(TASK_2 PUBLIC
                        DURLIB
                )
                message("TASK_2 Executable added")
        endif()

        # COMPILER DEFINITIONS.
        # target_compile_definitions(TASK_1 PUBLIC CLI_PLATFORM_WINDOWS)
        # target_compile_definitions(TASK_1 PUBLIC CLI_STATIC_LIBRARY)
        # target_compile_definitions(TASK_1 PUBLIC CLI_ENABLE_ASSERTS)

        # ENABLE PROFILING FOR DEBUG BUILS.
        # if(CMAKE_BUILD_TYPE STREQUAL Debug)
        # target_compile_definitions(TASK_1 PUBLIC CLI_DEBUG_PROFILING)
        # endif(CMAKE_BUILD_TYPE STREQUAL Debug)

        # TEST ENVIRONMENT
        # add_subdirectory("${PROJECT_SOURCE_DIR}/task_1/tests")
endif(WIN32)

# DOUBLE CHECKS IF THE SYSTEM IS RUNNING ON WINDOWS-X64 SYSTEM.
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
        message("PROJECT SUPPORTS ONLY X64 SYSTEMS.")
        return()
endif()