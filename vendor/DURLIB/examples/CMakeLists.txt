add_executable(DURLIB_EXAMPLES_FRACTIONS "${PROJECT_SOURCE_DIR}/examples/Fractions.cpp")
target_link_libraries(DURLIB_EXAMPLES_FRACTIONS PUBLIC DURLIB)
set_target_properties(DURLIB_EXAMPLES_FRACTIONS PROPERTIES OUTPUT_NAME "Durlib Fraction Example")
message("Fraction Example Added.")