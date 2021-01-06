set(pkginclude_HEADERS
  EDecayType.hh
  P6DExtDecayerPhysics.hh
)

set(libg4decayer_la_SOURCES
  pythia6_common_address.c
  Pythia6.cc
  G4Pythia6Decayer.cc
  G4Pythia6DecayerMessenger.cc
  P6DExtDecayerPhysics.cc
)


add_library(g4decayer ${libg4decayer_la_SOURCES})

set_target_properties(g4decayer PROPERTIES SOVERSION 0)

target_include_directories(g4decayer
    PRIVATE
    ${Geant4_INCLUDE_DIR}/../
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(g4decayer
    -L$ENV{OPT_SPHENIX}/lib
    Pythia6
)

install(TARGETS g4decayer)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/g4decayer/")
