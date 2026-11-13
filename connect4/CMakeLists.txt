
cmake_minimum_required(VERSION 3.16)

project( connect4 LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# console.out
add_executable( console.out 
  src/Game.cpp
  src/Player.cpp
  src/UiConsole.cpp
  src/main-console.cpp
)

