cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(sphenix-coresoftware LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# By default build shared libraries
OPTION(BUILD_SHARED_LIBS "Global flag to cause add_library to create shared libraries if on" ON)

find_package(Acts REQUIRED)
find_package(ROOT REQUIRED)
find_package(Geant4 REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(CGAL REQUIRED)
find_package(GSL REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Rave REQUIRED)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_subdirectory(simulation/g4simulation/g4bbc)
add_subdirectory(simulation/g4simulation/g4calo)
add_subdirectory(simulation/g4simulation/g4decayer)
add_subdirectory(simulation/g4simulation/g4detectors)
add_subdirectory(simulation/g4simulation/g4epd)
add_subdirectory(simulation/g4simulation/g4eval)
add_subdirectory(simulation/g4simulation/g4gdml)
add_subdirectory(simulation/g4simulation/g4intt)
add_subdirectory(simulation/g4simulation/g4main)
add_subdirectory(simulation/g4simulation/g4micromegas)
add_subdirectory(simulation/g4simulation/g4mvtx)
add_subdirectory(simulation/g4simulation/g4tpc)
add_subdirectory(simulation/g4simulation/g4vertex)
