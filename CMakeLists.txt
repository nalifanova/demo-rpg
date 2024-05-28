# set minimum cmake version
cmake_minimum_required(VERSION 3.28)
# project name, version and language
project(
    demo_rpg
    VERSION 0.1
    DESCRIPTION "A Demo RPG using C++"
    LANGUAGES CXX
)
# require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# ensure -std=c++XX instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

if (WIN32)
    set(CPP_VERSION -std=gnu++${CMAKE_CXX_STANDARD})
elseif (APPLE)
    set(CPP_VERSION -std=c++${CMAKE_CXX_STANDARD})
else ()
    set(CPP_VERSION -std=c++${CMAKE_CXX_STANDARD})
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-reorder")

# -- create a lib --
# add src files to var SRC_FILES
file(GLOB_RECURSE SRC_FILES src/*.cpp)
# create a demo_rpg_lib from SRC_FILES
add_library(${PROJECT_NAME}_lib STATIC ${SRC_FILES})
# include headers files
include_directories(include/demo_rpg/)
# add main.cpp as an executable endpoint
add_executable(${PROJECT_NAME} main.cpp)
# include the lib to main executable
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_lib)


# ----------- For including tests -----------
add_subdirectory(tests)
add_subdirectory(extern/googletest)
enable_testing()
