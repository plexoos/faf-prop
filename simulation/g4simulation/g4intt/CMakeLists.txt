set(pkginclude_HEADERS
  InttDeadMap.h
  InttDeadMapv1.h
  PHG4InttDigitizer.h
  PHG4InttDefs.h
  PHG4InttHitReco.h
  PHG4InttSubsystem.h
)

set(libg4intt_io_la_SOURCES
  g4intt_io_Dict.cxx
  InttDeadMap.cc
  InttDeadMapv1.cc
)

set(libg4intt_la_SOURCES
  PHG4InttDeadMapLoader.cc
  PHG4InttDetector.cc
  PHG4InttDisplayAction.cc
  PHG4InttDigitizer.cc
  PHG4InttHitReco.cc
  PHG4InttFPHXParameterisation.cc
  PHG4InttSteppingAction.cc
  PHG4InttSubsystem.cc
)

root_generate_dictionary(
  g4intt_io_Dict
  InttDeadMap.h
  InttDeadMapv1.h
  MODULE g4intt_io
  LINKDEF LinkDef.h
  OPTIONS -I${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(g4intt_io ${libg4intt_io_la_SOURCES})
add_library(g4intt ${libg4intt_la_SOURCES})

set_target_properties(g4intt_io PROPERTIES SOVERSION 0)
set_target_properties(g4intt PROPERTIES SOVERSION 0)

target_include_directories(g4intt_io
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/offline/framework
    #${CMAKE_SOURCE_DIR}/offline/database
    #${CMAKE_SOURCE_DIR}/offline/packages
    ${CMAKE_SOURCE_DIR}/simulation/g4simulation
    #${GSL_INCLUDE_DIRS}
    ${ROOT_INCLUDE_DIRS}
)

target_include_directories(g4intt
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/offline/database
    ${CMAKE_SOURCE_DIR}/offline/packages
    ${CMAKE_SOURCE_DIR}/simulation/g4simulation
    ${GSL_INCLUDE_DIRS}
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(g4intt_io
    g4detectors
    -L$ENV{OFFLINE_MAIN}/lib
    phool
)

target_link_libraries(g4intt
    g4intt_io
    g4detectors
    -L$ENV{OFFLINE_MAIN}/lib
    intt_io
)

install(TARGETS g4intt_io g4intt)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/g4intt")
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/libg4intt_io_rdict.pcm
    ${CMAKE_CURRENT_BINARY_DIR}/libg4intt_io.rootmap
    DESTINATION "lib/")
