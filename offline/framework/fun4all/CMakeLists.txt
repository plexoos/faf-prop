set(pkginclude_HEADERS
  Fun4AllBase.h
  Fun4AllDstInputManager.h
  Fun4AllDstOutputManager.h
  Fun4AllDummyInputManager.h
  Fun4AllHistoBinDefs.h
  Fun4AllHistoManager.h
  Fun4AllInputManager.h
  Fun4AllMemoryTracker.h
  Fun4AllNoSyncDstInputManager.h
  Fun4AllOutputManager.h
  Fun4AllReturnCodes.h
  Fun4AllServer.h
  Fun4AllSyncManager.h
  Fun4AllUtils.h
  PHTFileServer.h
  SubsysReco.h
  TDirectoryHelper.h
)

set(libfun4all_la_SOURCES
  Fun4AllDstInputManager.cc
  Fun4AllDstOutputManager.cc
  Fun4AllDummyInputManager.cc
  Fun4AllHistoManager.cc
  Fun4AllInputManager.cc
  Fun4AllMemoryTracker.cc
  Fun4AllNoSyncDstInputManager.cc
  Fun4AllOutputManager.cc
  Fun4AllServer.cc
  Fun4AllSyncManager.cc
  Fun4AllUtils.cc
  PHTFileServer.cc
)

add_library(fun4all ${libfun4all_la_SOURCES})
add_library(SubsysReco Fun4AllBase.cc)
add_library(TDirectoryHelper TDirectoryHelper.cc)

set_target_properties(fun4all PROPERTIES SOVERSION 0)
set_target_properties(SubsysReco PROPERTIES SOVERSION 0)
set_target_properties(TDirectoryHelper PROPERTIES SOVERSION 0)

target_include_directories(fun4all
    PRIVATE
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(TDirectoryHelper
    ROOT::Core
)

target_link_libraries(fun4all
    ROOT::Core
    SubsysReco
    TDirectoryHelper
    ${Boost_FILESYSTEM_LIBRARY}
    phool
    FROG
    ffaobjects
)

install(TARGETS fun4all SubsysReco TDirectoryHelper)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/fun4all/")
