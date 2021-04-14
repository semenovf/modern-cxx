add_executable(test_concepts test.cpp)
target_compile_options(test_concepts PRIVATE -fconcepts -std=c++17 -Wall -Wextra -Wpedantic)
