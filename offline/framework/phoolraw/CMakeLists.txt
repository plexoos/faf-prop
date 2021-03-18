set(pkginclude_HEADERS
  PHRawOManager.h
)

set(libphoolraw_la_SOURCES
  PHRawDataNode.cc
  PHRawOManager.cc
)

add_library(phoolraw ${libphoolraw_la_SOURCES})

set_target_properties(phoolraw PROPERTIES SOVERSION 0)

target_include_directories(phoolraw
    PRIVATE
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${ROOT_INCLUDE_DIRS}
    $ENV{OFFLINE_MAIN}/include
)

target_link_libraries(phoolraw
  ${ROOT_LIBRARIES}
  -L$ENV{OFFLINE_MAIN}/lib
  Event
)

install(TARGETS phoolraw)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/phoolraw/")
