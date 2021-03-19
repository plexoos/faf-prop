set(pkginclude_HEADERS
  TpcDefs.h
  TpcHit.h
  TpcClusterizer.h
  TpcSpaceChargeCorrection.h
  TpcClusterCleaner.h
)

set(libtpc_la_SOURCES
  TpcClusterizer.cc
  TpcSpaceChargeCorrection.cc
  TpcClusterCleaner.cc
)

set(libtpc_io_la_SOURCES
  TpcHit_Dict.cxx
  TpcDefs.cc
  TpcHit.cc
)

root_generate_dictionary(
  TpcHit_Dict
  TpcHit.h
  MODULE tpc_io
  LINKDEF LinkDef.h
  OPTIONS -I${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(tpc ${libtpc_la_SOURCES})
add_library(tpc_io ${libtpc_io_la_SOURCES})

set_target_properties(tpc PROPERTIES SOVERSION 0)
set_target_properties(tpc_io PROPERTIES SOVERSION 0)

target_include_directories(tpc
    PRIVATE
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/offline/packages
    ${CMAKE_SOURCE_DIR}/simulation/g4simulation
    ${ROOT_INCLUDE_DIRS}
)

target_include_directories(tpc_io
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/offline/packages
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(tpc
  tpc_io
  fun4all
  ${ROOT_Spectrum_LIBRARY}
)

target_link_libraries(tpc_io
  g4detectors_io
  track_io
  trackbase_historic_io
)

install(TARGETS tpc)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/tpc/")
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/libtpc_io_rdict.pcm
    ${CMAKE_CURRENT_BINARY_DIR}/libtpc_io.rootmap
    DESTINATION "lib/")
