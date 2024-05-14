cmake_minimum_required(VERSION 3.28)
project(demo_rpg)

set(CMAKE_CXX_STANDARD 20)

add_executable(demo_rpg
        src/main.cpp
        src/character_stats.h
        src/player_classes.h
        src/level_system.h
        src/tests.h
        src/tests.cpp
        src/player_character_delegate.h
)
