# GUIDE FOR BUILDING PROPER LIBRARY
# https://codingnest.com/basic-cmake-part-2/

cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(VERBOSE_LIST ON CACHE INTERNAL "")
set(MAIN_TEST ON)
set(EXAMPLES ON)
set(CMAKE_TOOLCHAIN_FILE "")
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})

project(DURLIB VERSION ${PROJECT_VERSION})

find_package(Git QUIET)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

# find_package(wxWidgets REQUIRED)
# find_package(OpenCV REQUIRED)

include(CTest)
enable_testing()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if(${VERBOSE_LIST})
        message("Project version: ${PROJECT_VERSION}")
        message("Toolchain status: ${CMAKE_TOOLCHAIN_FILE}")
        message("Cmake include current directory: ${CMAKE_INCLUDE_CURRENT_DIR}")
        message("CTest status: ${CPACK_PROJECT_NAME} version ${CPACK_PROJECT_VERSION};")
endif()

# CHECK IF SYSTEMS IS RUNNING WINDOWS AND ADD NECESSARY ATTRIBUTES.
if(WIN32)
        # ADD SOURCE FILES
        # DURLIB .CPP FILES
        file(GLOB_RECURSE DURLIB_CPP
                "${PROJECT_SOURCE_DIR}/durlib/Datatype/Date/DateMath.cpp"
                "${PROJECT_SOURCE_DIR}/durlib/Math/Rational/Fraction.cpp"
                "${PROJECT_SOURCE_DIR}/durlib/Math/Formulas/EarthCoordinates.cpp"
                "${PROJECT_SOURCE_DIR}/durlib/Math/Formulas/Utils.cpp"
                "${PROJECT_SOURCE_DIR}/durlib/Input/Input.cpp"
                "${PROJECT_SOURCE_DIR}/durlib/Input/Validation.cpp"
                "${PROJECT_SOURCE_DIR}/durlib/Log/Log.cpp"
                #"${PROJECT_SOURCE_DIR}/durlib/Serialization/Json/Jsonparse.cpp"
                #"${PROJECT_SOURCE_DIR}/durlib/Serialization/CSV/CSV.cpp"
                #"${PROJECT_SOURCE_DIR}/durlib/Serialization/CSV/CSVLL.cpp"
                #"${PROJECT_SOURCE_DIR}/durlib/Serialization/CSV/Algorithms/ALGO.cpp"
                "${PROJECT_SOURCE_DIR}/durlib/Database/sqlite3/core/database.cpp"
                "${PROJECT_SOURCE_DIR}/durlib/Database/sqlite3/item/item.cpp"
        )

        # DURLIB .H FILES
        file(GLOB_RECURSE DURLIB_H
                "${PROJECT_SOURCE_DIR}/durlib/Core/_CORE.h"
                "${PROJECT_SOURCE_DIR}/durlib/Datatype/Date/DateMath.h"
                "${PROJECT_SOURCE_DIR}/durlib/Math/Math.h"
                "${PROJECT_SOURCE_DIR}/durlib/Math/Rational/Fraction.h"
                "${PROJECT_SOURCE_DIR}/durlib/Math/Formulas/EarthCoordinates.h"
                "${PROJECT_SOURCE_DIR}/durlib/Math/Formulas/Utils.h"
                "${PROJECT_SOURCE_DIR}/durlib/Input/Input.h"
                "${PROJECT_SOURCE_DIR}/durlib/Input/Validation.h"
                "${PROJECT_SOURCE_DIR}/durlib/Log/Log.h"
                #"${PROJECT_SOURCE_DIR}/durlib/Serialization/Json/Jsonparse.h"
                #"${PROJECT_SOURCE_DIR}/durlib/Serialization/CSV/CSV.h"
                #"${PROJECT_SOURCE_DIR}/durlib/Serialization/CSV/CSVLL.h"
                #"${PROJECT_SOURCE_DIR}/durlib/Serialization/CSV/Algorithms/ALGO.h"
                "${PROJECT_SOURCE_DIR}/durlib/Database/sqlite3/core/database.h"
                "${PROJECT_SOURCE_DIR}/durlib/Database/sqlite3/item/item.h"
        )

        if(${VERBOSE_LIST})
                message("DURLIB source files added")
        endif()

        add_library(DURLIB STATIC ${DURLIB_CPP})
        target_compile_features(DURLIB PUBLIC cxx_std_17)
        set_target_properties(DURLIB PROPERTIES VERSION ${PROJECT_VERSION})
        # set_target_properties(DURLIB PROPERTIES OUTPUT_NAME "durlib")

        target_link_libraries(DURLIB PUBLIC
                fmt::fmt
                spdlog::spdlog
                jsoncpp_lib jsoncpp_object JsonCpp::JsonCpp

                # ${OpenCV_LIBS}
        )

        target_precompile_headers(DURLIB PUBLIC
                "${PROJECT_SOURCE_DIR}/durlib/PCH.h"
        )

        target_include_directories(DURLIB PUBLIC
                ${DURLIB_H}
                "${PROJECT_SOURCE_DIR}/."
                "${PROJECT_BINARY_DIR}/vendor/sqlite"
        )

        # COMPILER DEFINITIONS FOR DURLIB.
        target_compile_definitions(DURLIB PUBLIC DURLIB_PLATFORM_WINDOWS)
        target_compile_definitions(DURLIB PUBLIC DURLIB_STATIC_LIBRARY)
        target_compile_definitions(DURLIB PUBLIC DURLIB_ENABLE_ASSERTS)
        
        # ENABLE PROFILING FOR DEBUG BUILS.
        if(CMAKE_BUILD_TYPE STREQUAL Debug)
                target_compile_definitions(DURLIB PUBLIC DURLIB_DEBUG_PROFILING)
                target_compile_definitions(DURLIB PUBLIC DURLIB_ENABLE_DEBUG_LOG)
        endif(CMAKE_BUILD_TYPE STREQUAL Debug)

        if(${MAIN_TEST})
                add_subdirectory("${PROJECT_SOURCE_DIR}/tests")

                #add_executable(DURLIB_TEST_ENV "${PROJECT_SOURCE_DIR}/tests/main.cpp")
                #target_link_libraries(DURLIB_TEST_ENV PUBLIC DURLIB)

                #message("DURLIB MAIN CPP TEST EXECUTABLE ADDED.")
        endif()

        if(${EXAMPLES})
                add_subdirectory("${PROJECT_SOURCE_DIR}/examples")
        endif()
endif(WIN32)

# DOUBLE CHECKS IF THE SYSTEM IS RUNNING ON WINDOWS-X64 SYSTEM.
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
        message("DURLIB SUPPORTS ONLY X64 SYSTEMS.")
        return()
endif()

message("DURLIB SUCCESSFULLY ADDED.")