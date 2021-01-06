set(pkginclude_HEADERS
  PHG4MicromegasDigitizer.h
  PHG4MicromegasHitReco.h
  PHG4MicromegasSubsystem.h
)

set(libg4micromegas_la_SOURCES
  PHG4MicromegasSubsystem.cc
  PHG4MicromegasDetector.cc
  PHG4MicromegasDigitizer.cc
  PHG4MicromegasHitReco.cc
  PHG4MicromegasSteppingAction.cc
)

add_library(g4micromegas ${libg4micromegas_la_SOURCES})

set_target_properties(g4micromegas PROPERTIES SOVERSION 0)

target_include_directories(g4micromegas
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/offline/database
    ${CMAKE_SOURCE_DIR}/offline/packages
    ${CMAKE_SOURCE_DIR}/simulation/g4simulation
    ${GSL_INCLUDE_DIRS}
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(g4micromegas
    g4detectors
    g4testbench
    -L$ENV{OFFLINE_MAIN}/lib
    phool
    SubsysReco
    micromegas_io
)

install(TARGETS g4micromegas)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/g4micromegas/")
