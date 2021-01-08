set(pkginclude_HEADERS
  GlobalVertex.h
  GlobalVertexv1.h
  GlobalVertexFastSimReco.h
  GlobalVertexMap.h
  GlobalVertexMapv1.h
  GlobalVertexReco.h
)

set(libg4vertex_io_la_SOURCES
  g4vertex_io_Dict.cxx
  GlobalVertexv1.cc
  GlobalVertexMapv1.cc
)

set(libg4vertex_la_SOURCES
  GlobalVertexFastSimReco.cc
  GlobalVertexReco.cc
)

root_generate_dictionary(
  g4vertex_io_Dict
  GlobalVertex.h
  GlobalVertexv1.h
  GlobalVertexMap.h
  GlobalVertexMapv1.h
  MODULE g4vertex_io
  LINKDEF LinkDef.h
  OPTIONS -I${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(g4vertex_io ${libg4vertex_io_la_SOURCES})
add_library(g4vertex ${libg4vertex_la_SOURCES})

set_target_properties(g4vertex_io PROPERTIES SOVERSION 0)
set_target_properties(g4vertex PROPERTIES SOVERSION 0)

target_include_directories(g4vertex_io
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${ROOT_INCLUDE_DIRS}
)

target_include_directories(g4vertex
    PRIVATE
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/offline/packages
    ${CMAKE_SOURCE_DIR}/simulation/g4simulation
    ${GSL_INCLUDE_DIRS}
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(g4vertex
    g4detectors
    g4vertex_io
    g4bbc_io
    -L$ENV{OFFLINE_MAIN}/lib
    fun4all
    trackbase_historic_io
)

install(TARGETS g4vertex g4vertex_io)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/g4vertex/")
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/libg4vertex_io_rdict.pcm
    ${CMAKE_CURRENT_BINARY_DIR}/libg4vertex_io.rootmap
    DESTINATION "lib/"
)
