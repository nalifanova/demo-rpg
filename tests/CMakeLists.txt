# store all *.cpp file-paths from tests/ folder to TEST_SOURCES
file(GLOB_RECURSE TEST_SOURCES *.cpp)
# add TEST_SOURCES to an executable endpoint
add_executable(game_tests ${TEST_SOURCES})
# add a test called game_tests
add_test(NAME game_tests COMMAND run_tests)
# include the demo_rpg_lib and gtest to game_tests
target_link_libraries(game_tests PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)

# message(STATUS "tests/Files are ${TEST_SOURCES}") # TODO: debug
