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

if (WIN32)
    set(CPP_VERSION -std=gnu++${CMAKE_CXX_STANDARD})
elseif (APPLE)
    set(CPP_VERSION -std=c++${CMAKE_CXX_STANDARD})
else ()
    set(CPP_VERSION -std=c++${CMAKE_CXX_STANDARD})
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-reorder")

add_executable(${PROJECT_NAME}
        src/headers/character_stats.h
        src/headers/level_system.h
        src/headers/player_character_delegate.h
        src/headers/tests.h
        src/headers/types.h
        src/headers/buff.h
        src/headers/ability.h
        src/headers/core_stats.h
        src/headers/player_character.h
        src/headers/point_stack.h
        src/headers/item.h
        src/headers/item_manager.h
        src/headers/cleric.h
        src/headers/rogue.h
        src/headers/warrior.h
        src/headers/wizard.h
        src/headers/armor.h
        src/headers/weapon.h
        src/headers/potion.h
        src/main.cpp
        src/tests.cpp
        src/item.cpp
        src/ability.cpp
        src/armor.cpp
        src/buff.cpp
        src/cleric.cpp
        src/character_stats.cpp
        src/core_stats.cpp
        src/item.cpp
        src/level_system.cpp
        src/point_stack.cpp
        src/player_character.cpp
        src/player_character_delegate.cpp
        src/potion.cpp
        src/rogue.cpp
        src/warrior.cpp
        src/wizard.cpp
        src/weapon.cpp
        src/item_manager.cpp
)

# ----------- For including tests -----------
# NOTE: not sure it is correct
#       all src/*.cpp should be included
# add_library("${PROJECT_NAME}_lib" main.cpp tests.cpp)

# Path to headers
# target_include_directories("${PROJECT_NAME}_lib" PUBLIC ${PROJECT_SOURCE_DIR}/src/headers)

# add_subdirectory(tests)
# enable_testing()