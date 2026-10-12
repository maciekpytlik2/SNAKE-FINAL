cmake_minimum_required(VERSION 3.16)
project(SnakeSFML LANGUAGES CXX)

include(CheckCXXSourceCompiles)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SNAKE_USE_STD_MODULES "Use import std in ScoreManager.cpp on a supporting toolchain" OFF)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(SnakeSFML
    src/main.cpp
    src/Game.cpp
    src/Board.cpp
    src/Snake.cpp
    src/GameObject.cpp
    src/Food.cpp
    src/BonusFood.cpp
    src/Obstacle.cpp
    src/ScoreManager.cpp
    src/Renderer.cpp
    src/InputHandler.cpp
)

target_include_directories(SnakeSFML PRIVATE include)
target_link_libraries(SnakeSFML PRIVATE SFML::Graphics SFML::Window SFML::System)

if(SNAKE_USE_STD_MODULES)
    set(CMAKE_REQUIRED_FLAGS "-std=c++23")
    check_cxx_source_compiles(
        "import std;
         int main() { return 0; }"
        SNAKE_COMPILER_SUPPORTS_IMPORT_STD
    )
    unset(CMAKE_REQUIRED_FLAGS)

    if(SNAKE_COMPILER_SUPPORTS_IMPORT_STD)
        target_compile_features(SnakeSFML PRIVATE cxx_std_23)
        target_compile_definitions(SnakeSFML PRIVATE SNAKE_USE_STD_MODULES=1)
    else()
        message(WARNING "SNAKE_USE_STD_MODULES requested, but this toolchain does not support 'import std;'. Falling back to #include in ScoreManager.cpp.")
    endif()
endif()

if(APPLE)
    set_target_properties(SnakeSFML PROPERTIES
        BUILD_RPATH "/opt/homebrew/lib;/usr/local/lib"
    )
endif()
