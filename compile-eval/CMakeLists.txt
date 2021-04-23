# add_executable(test_templates test_templates.cpp)
# set_property(TARGET test_templates PROPERTY CXX_STANDARD 98)

# add_executable(test_constexpr_simple test_constexpr_simple.cpp)
# set_property(TARGET test_constexpr_simple PROPERTY CXX_STANDARD 11)

file(GLOB determinantH "determinant.h")

add_executable(test_constexpr test_constexpr.cpp)
add_executable(determinantSolution determinantH)

set_property(TARGET test_constexpr determinantSolution PROPERTY CXX_STANDARD 14)
