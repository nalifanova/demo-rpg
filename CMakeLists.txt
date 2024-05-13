cmake_minimum_required(VERSION 3.28)
project(demo_rpg)

set(CMAKE_CXX_STANDARD 20)

add_executable(demo_rpg
        src/main.cpp
        src/warrior.h
        src/stat_types.h
        src/character.h
        src/stat_block.h
        src/wizard.h
        src/cleric.h
        src/rogue.h
        src/level_system.h
        src/tests.h
        src/tests.cpp
)
