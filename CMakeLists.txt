cmake_minimum_required(VERSION 3.15)

project(FlappyBird)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

set(RESOURCE_FILES Resources)

add_executable(FlappyBird main.cpp game-engine.cpp game-engine.hpp state.hpp
  state-manager.hpp asset-manager.cpp asset-manager.hpp
  definitions.hpp main-menu-state.cpp main-menu-state.hpp game-state.cpp game-state.hpp game-over-state.cpp
  game-over-state.hpp pipe.cpp pipe.hpp land.cpp land.hpp bird.cpp bird.hpp)


find_package(SFML COMPONENTS audio graphics window system REQUIRED)
set(SFML_STATIC_LIBRARIES true)

target_link_libraries(FlappyBird sfml-audio sfml-graphics sfml-window sfml-system  )

target_link_libraries(FlappyBird ${CMAKE_EXE_LINKER_FLAGS})