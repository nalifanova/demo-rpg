cmake_minimum_required(VERSION 3.28)
project(
        demo_rpg
        VERSION 0.1
        DESCRIPTION "A Demo RPG using C++"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME}
        src/headers/character_stats.h
        src/headers/level_system.h
        src/headers/player_classes.h
        src/headers/player_character_delegate.h
        src/headers/tests.h
        src/main.cpp
        src/tests.cpp
)

# ----------- For including tests -----------
# NOTE: not sure it is correct
#       all src/*.cpp should be included
# add_library("${PROJECT_NAME}_lib" main.cpp tests.cpp)

# Path to headers
# target_include_directories("${PROJECT_NAME}_lib" PUBLIC ${PROJECT_SOURCE_DIR}/src/headers)

# add_subdirectory(tests)
# enable_testing()