cmake_minimum_required(VERSION 3.14)
project(OrderMatchingEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Core library
add_library(engine_core
  src/Order.cpp
  src/OrderBook.cpp
  src/MatchingEngine.cpp
  src/Trade.cpp
)
target_include_directories(engine_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Enable testing
enable_testing()

# Test executables
add_executable(test_order test/test_order.cpp)
target_link_libraries(test_order PRIVATE engine_core GTest::gtest_main)

add_executable(test_orderbook test/test_orderbook.cpp)
target_link_libraries(test_orderbook PRIVATE engine_core GTest::gtest_main)

add_executable(test_matchingengine test/test_matchingengine.cpp)
target_link_libraries(test_matchingengine PRIVATE engine_core GTest::gtest_main)

add_executable(test_integration test/test_integration.cpp)
target_link_libraries(test_integration PRIVATE engine_core GTest::gtest_main)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(test_order)
gtest_discover_tests(test_orderbook)
gtest_discover_tests(test_matchingengine)
gtest_discover_tests(test_integration)
