file(GLOB_RECURSE Fraction_CPP
                                        "${PROJECT_SOURCE_DIR}/task_1/source/Fraction.cpp"
)
file(GLOB_RECURSE Fraction_H
                                        "${PROJECT_SOURCE_DIR}/task_1/source/Fraction.h"
)

add_executable(Fraction_Test    "Fraction_Test.cpp"
                                ${Fraction_CPP}
)

target_link_libraries(Fraction_Test PUBLIC
                                            durlib
)

target_include_directories(Fraction_Test PUBLIC
                                                #${Fraction_H}
                                                "${PROJECT_SOURCE_DIR}/task_1/source"
)

add_test(fraction_gtests Fraction_Test)

add_executable(Custom_Test    "Custom_Test.cpp"
                                ${Fraction_CPP}
)

target_link_libraries(Custom_Test PUBLIC
                                            durlib
)

target_include_directories(Custom_Test PUBLIC
                                                #${Fraction_H}
                                                "${PROJECT_SOURCE_DIR}/task_1/source"
)