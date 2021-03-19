set(pkginclude_HEADERS
  FROG.h
)

set(libFROG_la_SOURCES
  FROG.cc
)

add_library(FROG ${libFROG_la_SOURCES})

set_target_properties(FROG PROPERTIES SOVERSION 0)

target_include_directories(FROG
    PRIVATE
    ${CMAKE_SOURCE_DIR}/offline/framework
    $ENV{OPT_SPHENIX}/include
)

target_link_libraries(FROG
    -L$ENV{OPT_SPHENIX}/lib
    odbc++
)

install(TARGETS FROG)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/FROG/")
install(FILES CreateFileList.pl DESTINATION "bin/")
