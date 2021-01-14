set(pkginclude_HEADERS
  HcalRawTowerBuilder.h
  RawTowerBuilder.h
  RawTowerBuilderByHitIndex.h
  RawTowerDigitizer.h
)

set(libg4calo_la_SOURCES
  HcalRawTowerBuilder.cc
  RawTowerBuilder.cc
  RawTowerBuilderByHitIndex.cc
  RawTowerDigitizer.cc
)


add_library(g4calo ${libg4calo_la_SOURCES})

set_target_properties(g4calo PROPERTIES SOVERSION 0)

target_include_directories(g4calo
    PRIVATE
    ${CMAKE_SOURCE_DIR}/offline/database
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/offline/packages
    ${CMAKE_SOURCE_DIR}/simulation/g4simulation
    ${GSL_INCLUDE_DIRS}
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(g4calo
    g4detectors_io
    g4testbench
    phg4hit
    -L$ENV{OFFLINE_MAIN}/lib
    fun4all
    phool
    SubsysReco
    phparameter
    calo_io
    ${GSL_CBLAS_LIBRARY}
    ${GSL_LIBRARY}
)

install(TARGETS g4calo)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/g4calo/")
