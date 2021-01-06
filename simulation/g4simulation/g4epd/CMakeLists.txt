set(pkginclude_HEADERS
  PHG4EPDetector.h
  PHG4EPSteppingAction.h
  PHG4EPDSubsystem.h
)

set(libg4epd_la_SOURCES
  PHG4EPDetector.cc
  PHG4EPSteppingAction.cc
  PHG4EPDSubsystem.cc
)

add_library(g4epd ${libg4epd_la_SOURCES})

set_target_properties(g4epd PROPERTIES SOVERSION 0)

target_include_directories(g4epd
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/offline/database
    ${CMAKE_SOURCE_DIR}/simulation/g4simulation
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(g4epd
    g4detectors
    -L$ENV{OFFLINE_MAIN}/lib
    phool
)

install(TARGETS g4epd)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/g4epd/")
