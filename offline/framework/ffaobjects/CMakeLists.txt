set(pkginclude_HEADERS
  FlagSave.h
  FlagSavev1.h
  RunHeader.h
  RunHeaderv1.h
  SyncDefs.h
  SyncObject.h
  SyncObjectv1.h
  EventHeader.h
  EventHeaderv1.h
  EventHeaderv2.h
)

set(libffaobjects_la_SOURCES
  ffaobjects_Dict.cxx
  FlagSavev1.cc
  RunHeader.cc
  RunHeaderv1.cc
  SyncObject.cc
  SyncObjectv1.cc
  EventHeader.cc
  EventHeaderv1.cc
  EventHeaderv2.cc
)

root_generate_dictionary(
  ffaobjects_Dict
  FlagSave.h
  FlagSavev1.h
  RunHeader.h
  RunHeaderv1.h
  SyncObject.h
  SyncObjectv1.h
  EventHeader.h
  EventHeaderv1.h
  EventHeaderv2.h
  MODULE ffaobjects
  LINKDEF LinkDef.h
  OPTIONS -I${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(ffaobjects ${libffaobjects_la_SOURCES})

set_target_properties(ffaobjects PROPERTIES SOVERSION 0)

target_include_directories(ffaobjects
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(ffaobjects
    phool
)

install(TARGETS ffaobjects)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/ffaobjects/")
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/libffaobjects_rdict.pcm
    ${CMAKE_CURRENT_BINARY_DIR}/libffaobjects.rootmap
    DESTINATION "lib/")
