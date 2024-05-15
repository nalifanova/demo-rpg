# Add Google Test
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

# To prevent conflicts with Google Test
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Make test executable file
add_executable(run_tests test_1.cpp)

# Add google test and project libs
target_link_libraries(run_tests gtest_main ) # demo_rpg_lib

# Tests registration
include(GoogleTest)
gtest_discover_tests(runTests)