set(pkginclude_HEADERS
  getClass.h
  PHCompositeNode.h
  PHDataNode.h
  PHDataNodeIterator.h
  PHFlag.h
  PHIODataNode.h
  PHIOManager.h
  PHLog.h
  PHNode.h
  PHNodeIOManager.h
  PHNodeIntegrate.h
  PHNodeOperation.h
  PHNodeReset.h
  PHNodeIterator.h
  PHObject.h
  phool.h
  phooldefs.h
  PHOperation.h
  PHRandomSeed.h
  PHPointerList.h
  PHPointerListIterator.h
  PHTimer.h
  PHTimeServer.h
  PHTimeStamp.h
  PHTypedNodeIterator.h
  recoConsts.h
)

set(libphool_la_SOURCES
  phool_Dict.cxx
  PHCompositeNode.cc
  PHFlag.cc
  PHMessage.cc
  PHNode.cc
  PHNodeIOManager.cc
  PHNodeIntegrate.cc
  PHNodeIterator.cc
  PHNodeReset.cc
  PHObject.cc
  PHOperation.cc
  PHRandomSeed.cc
  PHTimer.cc
  PHTimeServer.cc
  PHTimeStamp.cc
  recoConsts.cc
)

root_generate_dictionary(
  phool_Dict
  PHObject.h
  PHTimeStamp.h
  MODULE phool
  LINKDEF LinkDef.h
  OPTIONS -I${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(phool ${libphool_la_SOURCES})

set_target_properties(phool PROPERTIES SOVERSION 0)

target_include_directories(phool
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${ROOT_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(phool
    ${ROOT_LIBRARIES}
)

install(TARGETS phool)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/phool/")
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/libphool_rdict.pcm
    ${CMAKE_CURRENT_BINARY_DIR}/libphool.rootmap
    DESTINATION "lib/")
