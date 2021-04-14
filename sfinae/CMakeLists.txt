find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_advance test_advance.cpp)
target_link_libraries(test_advance GTest::GTest GTest::Main Threads::Threads)

add_executable(test_set test_set.cpp)
target_link_libraries(test_set GTest::GTest GTest::Main Threads::Threads)

set_property(TARGET test_advance PROPERTY CXX_STANDARD 14)
set_property(TARGET test_set PROPERTY CXX_STANDARD 14)

