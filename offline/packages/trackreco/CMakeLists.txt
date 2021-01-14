set(pkginclude_HEADERS
  ActsTransformations.h
  ActsTrack.h
  ActsTrackingGeometry.h
  ActsSurfaceMaps.h
  ActsEvaluator.h
  AssocInfoContainer.h
  CellularAutomaton.h
  CellularAutomaton_v1.h
  HelixHoughBin.h
  HelixHoughBin_v1.h
  HelixHoughFuncs.h
  HelixHoughFuncs_v1.h
  HelixHoughSpace.h
  HelixHoughSpace_v1.h
  HelixKalmanFilter.h
  MakeActsGeometry.h
  PHGenFitTrackProjection.h
  PHGenFitTrkFitter.h
  PHActsSourceLinks.h
  PHActsTracks.h
  PHActsTrkProp.h
  PHActsSiliconSeeding.h
  PHActsInitialVertexFinder.h
  PHActsVertexFinder.h
  PHActsTrkFitter.h
  PHActsVertexFitter.h
  PHActsTrackProjection.h
  PHGenFitTrkProp.h
  PHHoughSeeding.h
  PHRTreeSeeding.h
  PHCASeeding.h
  PHInitVertexing.h
  PHInitZVertexing.h
  PHSiliconTpcTrackMatching.h
  PHMicromegasTpcTrackMatching.h
  PHSiliconTruthTrackSeeding.h
  PHTpcClusterMover.h
  PHTpcResiduals.h
  PHTrackPropagating.h
  PHTrackSeeding.h
  PHTrackFitting.h
  PHTrackSetMerging.h
  PHTruthClustering.h
  PHTruthTrackSeeding.h
  PHTruthSiliconAssociation.h
  PHTruthVertexing.h
  VertexFitter.h
  PHRaveVertexing.h
  GPUTPCBaseTrackParam.h
  GPUTPCTrackLinearisation.h
  GPUTPCTrackParam.h
)

set(libtrack_reco_io_la_SOURCES
  track_reco_io_Dict.cxx
  AssocInfoContainer.cc
  CellularAutomaton_v1.cc
  HelixHoughBin_v1.cc
  HelixHoughFuncs_v1.cc
  HelixHoughSpace_v1.cc
  HelixKalmanFilter.cc
  VertexFitter.cc
  GPUTPCTrackParam.cxx
)

set(libtrack_reco_la_SOURCES
  ActsTransformations.cc
  ActsEvaluator.cc
  MakeActsGeometry.cc
  PHActsSiliconSeeding.cc
  PHActsSourceLinks.cc
  PHActsTracks.cc
  PHActsTrkProp.cc
  PHActsTrkFitter.cc
  PHActsInitialVertexFinder.cc
  PHActsVertexFinder.cc
  PHActsVertexFitter.cc
  PHActsTrackProjection.cc
  PHTpcResiduals.cc
  PHInitVertexing.cc
  PHInitZVertexing.cc
  PHTrackSeeding.cc
  PHTrackSetMerging.cc
  PHTrackPropagating.cc
  PHTrackFitting.cc
  PH3DVertexing.cc
  PHTpcClusterMover.cc
  PHTruthClustering.cc
  PHTruthVertexing.cc
  PHSiliconTpcTrackMatching.cc
  PHMicromegasTpcTrackMatching.cc
  PHTruthTrackSeeding.cc
  PHSiliconTruthTrackSeeding.cc
  PHTruthSiliconAssociation.cc
  PHHoughSeeding.cc
  PHRTreeSeeding.cc
  PHCASeeding.cc
  PHGenFitTrkProp.cc
  PHGenFitTrkFitter.cc
  PHGenFitTrackProjection.cc
  PHRaveVertexing.cc
)

root_generate_dictionary(
  track_reco_io_Dict
  AssocInfoContainer.h
  HelixHoughBin.h
  HelixHoughBin_v1.h
  HelixHoughFuncs.h
  HelixHoughFuncs_v1.h
  HelixHoughSpace.h
  HelixHoughSpace_v1.h
  MODULE track_reco_io
  LINKDEF LinkDef.h
  OPTIONS -I${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(track_reco_io ${libtrack_reco_io_la_SOURCES})
add_library(track_reco ${libtrack_reco_la_SOURCES})


target_compile_definitions(track_reco_io PUBLIC RAVE RaveDllExport=)
target_compile_definitions(track_reco PUBLIC RAVE RaveDllExport=)

set_target_properties(track_reco_io PROPERTIES SOVERSION 0)
set_target_properties(track_reco PROPERTIES SOVERSION 0)

target_include_directories(track_reco_io
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/offline/packages
    ${CMAKE_SOURCE_DIR}/offline/packages/HelixHough
    ${Rave_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}/eigen3
    ${ROOT_INCLUDE_DIRS}
    $ENV{OFFLINE_MAIN}/include
    $ENV{OFFLINE_MAIN}/include/HelixHough
    $ENV{OFFLINE_MAIN}/include/ActsFatras
)

target_include_directories(track_reco
    PRIVATE
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/offline/packages
    ${CMAKE_SOURCE_DIR}/simulation/g4simulation
    ${Rave_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}/eigen3
    ${GSL_INCLUDE_DIRS}
    ${ROOT_INCLUDE_DIRS}
    $ENV{OFFLINE_MAIN}/include
    $ENV{OFFLINE_MAIN}/include/ActsFatras
)

target_link_libraries(track_reco_io
    -L$ENV{OFFLINE_MAIN}/lib
    phool
    HelixHough
)

target_link_libraries(track_reco
    g4testbench
    g4detectors
    track_reco_io
    g4bbc_io
    g4tpc
    g4intt
    g4mvtx
    g4eval
    ActsCore
    ActsFatras
    ActsPluginTGeo
    ActsPluginJson
    -L$ENV{OFFLINE_MAIN}/lib
    fun4all
    SubsysReco
    FitNewton
    Seamstress
    -L$ENV{OFFLINE_MAIN}/lib64
    ActsExamplesCommon
    ActsExamplesFitting
    ActsExamplesTrackFinding
    ActsExamplesDetectorTGeo
    ActsExamplesFramework
    ActsExamplesIoRoot
    ActsExamplesMagneticField
    genfit2
    genfit2exp
    PHGenFit
    micromegas_io
    mvtx_io
    intt_io
    trackbase_historic_io
    calo_io
    phparameter
    ${GSL_CBLAS_LIBRARY}
    ${GSL_LIBRARY}
)

install(TARGETS track_reco track_reco_io)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/track_reco/")
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/libtrack_reco_io_rdict.pcm
    ${CMAKE_CURRENT_BINARY_DIR}/libtrack_reco_io.rootmap
    DESTINATION "lib/"
)
