add_executable(tdiff tdiff.cc)

target_include_directories(tdiff
    PRIVATE
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/simulation/g4simulation
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(tdiff
    phg4hit
    g4detectors
    g4micromegas
    g4intt
    g4mvtx
    ${ROOT_Core_LIBRARY}
    ${ROOT_RIO_LIBRARY}
    ${ROOT_Tree_LIBRARY}
)
