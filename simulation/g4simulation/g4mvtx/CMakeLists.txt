set(pkginclude_HEADERS
  PHG4MvtxDefs.h 
  PHG4MvtxHitReco.h 
  PHG4MvtxSubsystem.h 
  PHG4EICMvtxSubsystem.h 
  PHG4MvtxDigitizer.h
)

set(libg4mvtx_la_SOURCES
  PHG4MvtxHitReco.cc 
  PHG4MvtxDetector.cc 
  PHG4EICMvtxDetector.cc 
  PHG4MvtxDisplayAction.cc 
  PHG4MvtxSteppingAction.cc 
  PHG4EICMvtxSteppingAction.cc 
  PHG4MvtxSubsystem.cc 
  PHG4EICMvtxSubsystem.cc 
  PHG4MvtxDigitizer.cc
)

add_library(g4mvtx ${libg4mvtx_la_SOURCES})

set_target_properties(g4mvtx PROPERTIES SOVERSION 0)

target_include_directories(g4mvtx
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/offline/database
    ${CMAKE_SOURCE_DIR}/offline/packages
    ${CMAKE_SOURCE_DIR}/simulation/g4simulation
    ${GSL_INCLUDE_DIRS}
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(g4mvtx
    phg4hit
    g4detectors
    fun4all 
    -L$ENV{OFFLINE_MAIN}/lib
    track_io 
    mvtx_io
)

install(TARGETS g4mvtx)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/g4mvtx/")
