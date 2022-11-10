cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})

project(durlib VERSION ${PROJECT_VERSION})

find_package(Git QUIET)

set(CMAKE_PREFIX_PATH "C:\\Libraries\\Build\\x64\\msvc17\\fmt")
find_package(fmt CONFIG REQUIRED)
set(CMAKE_PREFIX_PATH "C:\\Libraries\\Build\\x64\\msvc17\\spdlog")
find_package(spdlog CONFIG REQUIRED)

set(CMAKE_TOOLCHAIN_FILE "C:\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
set(CMAKE_PREFIX_PATH "C:\\vcpkg\\installed\\x64-windows\\share\\jsoncpp")
find_package(jsoncpp CONFIG REQUIRED)

# find_package(wxWidgets REQUIRED)
# find_package(OpenCV REQUIRED)

# include(CTest)
# enable_testing()
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

# message("Project version: ${PROJECT_VERSION}")
# message("Toolchain status: ${CMAKE_TOOLCHAIN_FILE}")
# message("Cmake include current directory: ${CMAKE_INCLUDE_CURRENT_DIR}")
# message("CTest status: ${CPACK_PROJECT_NAME} version ${CPACK_PROJECT_VERSION};")

# CHECK IF SYSTEMS IS RUNNING WINDOWS AND ADD NECESSARY ATTRIBUTES.
if(WIN32)
        # ADD SOURCE FILES
        # durlib .CPP FILES
        file(GLOB_RECURSE durlib_CPP
                                        "${PROJECT_SOURCE_DIR}/durlib/Core/*.cpp"
                                        "${PROJECT_SOURCE_DIR}/durlib/Datatype/Date/*.cpp"
                                        "${PROJECT_SOURCE_DIR}/durlib/Input/*.cpp"
                                        "${PROJECT_SOURCE_DIR}/durlib/Log/*.cpp"
                                        "${PROJECT_SOURCE_DIR}/durlib/Serialization/Json/*.cpp"
        )
        # durlib .H FILES
        file(GLOB_RECURSE durlib_H
                                        "${PROJECT_SOURCE_DIR}/durlib/Core/*.h"
                                        "${PROJECT_SOURCE_DIR}/durlib/Datatype/Date/*.h"
                                        "${PROJECT_SOURCE_DIR}/durlib/Input/*.h"
                                        "${PROJECT_SOURCE_DIR}/durlib/Log/*.h"
                                        "${PROJECT_SOURCE_DIR}/durlib/Serialization/Json/*.h"
        )

        message("durlib source files added")

        add_library(durlib STATIC ${durlib_CPP})
        set_target_properties(durlib PROPERTIES VERSION ${PROJECT_VERSION})

        target_link_libraries(durlib PUBLIC
                                        fmt::fmt
                                        spdlog::spdlog
                                        jsoncpp_lib jsoncpp_object JsonCpp::JsonCpp
                                        #${OpenCV_LIBS}
        )

        target_precompile_headers(durlib PUBLIC
                                        "${PROJECT_SOURCE_DIR}/durlib/PCH.h"
        )

        target_include_directories(durlib PUBLIC
                                        ${durlib_H}
                                        "${PROJECT_SOURCE_DIR}/."
        )

        # message("Executable added")

        # COMPILER DEFINITIONS FOR durlib.
        target_compile_definitions(durlib PUBLIC durlib_PLATFORM_WINDOWS)
        target_compile_definitions(durlib PUBLIC durlib_STATIC_LIBRARY)
        target_compile_definitions(durlib PUBLIC durlib_ENABLE_ASSERTS)

        # ENABLE PROFILING FOR DEBUG BUILS.
        if(CMAKE_BUILD_TYPE STREQUAL Debug)
                target_compile_definitions(durlib PUBLIC durlib_DEBUG_PROFILING)
        endif(CMAKE_BUILD_TYPE STREQUAL Debug)

endif (WIN32)

# DOUBLE CHECKS IF THE SYSTEM IS RUNNING ON WINDOWS-X64 SYSTEM.
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)

        message("durlib SUPPORTS ONLY X64 SYSTEMS.")
        return()

endif()