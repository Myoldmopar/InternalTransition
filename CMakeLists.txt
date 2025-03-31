cmake_minimum_required(VERSION 3.30)
project(InternalTransition)
set(CMAKE_CXX_STANDARD 20)

# keep this list to reuse it
set(LIB_FILES src/transition.cpp src/transition.h src/file_format.h src/file_format.cpp)

# get google test and enable it
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)

# add the main executable
add_executable(InternalTransition src/main.cpp ${LIB_FILES})
target_include_directories(InternalTransition PRIVATE src vendor)

# add the unit test executable and discover all tests with the helper
add_executable(InternalTransitionTest tst/test.cpp ${LIB_FILES})
target_include_directories(InternalTransitionTest PRIVATE src vendor)
target_link_libraries(
        InternalTransitionTest
        GTest::gtest_main
)
gtest_discover_tests(InternalTransitionTest)
