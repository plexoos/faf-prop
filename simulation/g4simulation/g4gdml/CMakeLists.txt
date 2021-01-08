set(pkginclude_HEADERS
  PHG4GDMLUtility.hh
  PHG4GDMLConfig.hh
)

set(libg4gdml_la_SOURCES
  PHG4GDMLWrite.cc
  PHG4GDMLWriteDefine.cc
  PHG4GDMLWriteMaterials.cc
  PHG4GDMLWriteSolids.cc
  PHG4GDMLWriteSetup.cc
  PHG4GDMLWriteParamvol.cc
  PHG4GDMLWriteStructure.cc
  PHG4GDMLUtility.cc
)


add_library(g4gdml ${libg4gdml_la_SOURCES})

set_target_properties(g4gdml PROPERTIES SOVERSION 0)

target_include_directories(g4gdml
    PRIVATE
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${Geant4_INCLUDE_DIR}/../
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(g4gdml
    -L$ENV{OFFLINE_MAIN}/lib
    phool
    SubsysReco
    fun4all
)

install(TARGETS g4gdml)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/g4gdml/")
