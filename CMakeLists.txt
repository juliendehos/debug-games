
cmake_minimum_required( VERSION 3.16 )

project( piebill )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################################################
# SFML3
###############################################################################

find_package( SFML COMPONENTS Graphics )
if(NOT SFML_FOUND)
  include(FetchContent)
  FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
  FetchContent_MakeAvailable(SFML)
endif()

add_executable( piebill-sfml
  src/Game.cpp
  src/ViewSfml.cpp
  src/main-sfml.cpp )
target_link_libraries( piebill-sfml SFML::Graphics )

###############################################################################
# SDL2
###############################################################################

find_package( PkgConfig REQUIRED )
pkg_check_modules( PKG_SDL2 REQUIRED sdl2 SDL2_ttf SDL2_image )
add_executable( piebill-sdl
  src/Game.cpp
  src/ViewSdl.cpp
  src/main-sdl.cpp )
target_include_directories( piebill-sdl PRIVATE ${PKG_SDL2_INCLUDE_DIRS} )
target_link_libraries( piebill-sdl ${PKG_SDL2_LIBRARIES} )

###############################################################################
# install
###############################################################################

install( 
  TARGETS 
  piebill-sfml
  piebill-sdl
  DESTINATION bin )

install( 
  FILES 
  data/arial.ttf 
  data/bill-smile.png 
  data/bill-pie.png 
  data/desk.png 
  data/pie.png
  DESTINATION data )

