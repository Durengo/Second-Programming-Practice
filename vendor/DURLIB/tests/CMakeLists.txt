include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

if(${VERBOSE_LIST})
        message("Fetch Content: ${FetchContent}")
        message("Google Test: ${googletest}")
endif()

add_executable(MathTest "${PROJECT_SOURCE_DIR}/tests/durlib_math/FractionTest.cpp")
set_target_properties(MathTest PROPERTIES OUTPUT_NAME "Durlib Math GTest")
target_link_libraries(MathTest PUBLIC GTest::GTest DURLIB)
add_test(MathGTest MathTest)

message("DURLIB GTEST SUITE ADDED.")