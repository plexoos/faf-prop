set(pkginclude_HEADERS
  BbcVertex.h
  BbcVertexv1.h
  BbcVertexMap.h
  BbcVertexMapv1.h
  BbcVertexFastSimReco.h
)

set(libg4bbc_io_la_SOURCES
  g4bbc_io_Dict.cxx
  BbcVertexv1.cc
  BbcVertexMapv1.cc
)

set(libg4bbc_la_SOURCES
  BbcVertexFastSimReco.cc
)

root_generate_dictionary(
  g4bbc_io_Dict
  BbcVertex.h
  BbcVertexv1.h
  BbcVertexMap.h
  BbcVertexMapv1.h
  MODULE g4bbc_io
  LINKDEF LinkDef.h
  OPTIONS -I${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(g4bbc_io ${libg4bbc_io_la_SOURCES})
add_library(g4bbc ${libg4bbc_la_SOURCES})

set_target_properties(g4bbc_io PROPERTIES SOVERSION 0)
set_target_properties(g4bbc PROPERTIES SOVERSION 0)

target_include_directories(g4bbc_io
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${ROOT_INCLUDE_DIRS}
)

target_include_directories(g4bbc
    PRIVATE
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/simulation/g4simulation
    ${GSL_INCLUDE_DIRS}
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(g4bbc_io
    -L$ENV{OFFLINE_MAIN}/lib
    phool
)

target_link_libraries(g4bbc
    g4bbc_io
    g4detectors
    fun4all
)

install(TARGETS g4bbc_io g4bbc)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/g4bbc/")
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/libg4bbc_io_rdict.pcm
    ${CMAKE_CURRENT_BINARY_DIR}/libg4bbc_io.rootmap
    DESTINATION "lib/"
)
