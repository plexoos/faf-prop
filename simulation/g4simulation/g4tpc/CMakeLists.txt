set(pkginclude_HEADERS
  PHG4TpcElectronDrift.h
  PHG4TpcPadPlane.h
  PHG4TpcPadPlaneReadout.h
  PHG4TpcDigitizer.h
  PHG4TpcSubsystem.h
  PHG4TpcEndCapSubsystem.h
  PHG4TpcDistortion.h
)

set(libg4tpc_la_SOURCES
  PHG4TpcDetector.cc
  PHG4TpcEndCapDetector.cc
  PHG4TpcDigitizer.cc
  PHG4TpcDisplayAction.cc
  PHG4TpcEndCapDisplayAction.cc
  PHG4TpcDistortion.cc
  PHG4TpcElectronDrift.cc
  PHG4TpcPadPlane.cc
  PHG4TpcPadPlaneReadout.cc
  PHG4TpcSteppingAction.cc
  PHG4TpcEndCapSteppingAction.cc
  PHG4TpcSubsystem.cc
  PHG4TpcEndCapSubsystem.cc
)

add_library(g4tpc ${libg4tpc_la_SOURCES})

set_target_properties(g4tpc PROPERTIES SOVERSION 0)

target_include_directories(g4tpc
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/offline/database
    ${CMAKE_SOURCE_DIR}/offline/packages
    ${CMAKE_SOURCE_DIR}/simulation/g4simulation
    ${GSL_INCLUDE_DIRS}
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(g4tpc
    phg4hit
    g4detectors
    -L$ENV{OFFLINE_MAIN}/lib
    phool
    phparameter
    tpc_io
)

install(TARGETS g4tpc)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/g4tpc/")
