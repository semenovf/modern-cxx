add_executable(test_constexpr_map test.cpp ../catch-main.cpp)
set_property(TARGET test_constexpr_map PROPERTY CXX_STANDARD 17)
target_include_directories(test_constexpr_map PRIVATE ..)
