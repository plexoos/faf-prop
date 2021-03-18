set(pkginclude_HEADERS
  BaseTruthEval.h
  CaloEvalStack.h
  CaloEvaluator.h
  CaloRawClusterEval.h
  CaloRawTowerEval.h
  CaloTruthEval.h
  JetEvalStack.h
  JetEvaluator.h
  JetRecoEval.h
  JetTruthEval.h
  MomentumEvaluator.h
  PHG4DstCompressReco.h
  PHG4DSTReader.h
  SvtxEvalStack.h
  SvtxEvaluator.h
  SvtxHitEval.h
  SvtxClusterEval.h
  SvtxTrackEval.h
  SvtxTruthEval.h
  SvtxVertexEval.h
)

set(libg4eval_la_SOURCES
  BaseTruthEval.cc
  CaloEvalStack.cc
  CaloTruthEval.cc
  CaloRawTowerEval.cc
  CaloRawClusterEval.cc
  CaloEvaluator.cc
  JetEvalStack.cc
  JetTruthEval.cc
  JetRecoEval.cc
  JetEvaluator.cc
  PHG4DSTReader.cc
  SvtxEvalStack.cc
  SvtxTruthEval.cc
  SvtxHitEval.cc
  SvtxClusterEval.cc
  SvtxTrackEval.cc
  SvtxVertexEval.cc
  SvtxEvaluator.cc
  MomentumEvaluator.cc
  PHG4DstCompressReco.cc
)

add_library(g4eval ${libg4eval_la_SOURCES})

set_target_properties(g4eval PROPERTIES SOVERSION 0)

target_include_directories(g4eval
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/offline/database
    ${CMAKE_SOURCE_DIR}/offline/packages
    ${CMAKE_SOURCE_DIR}/simulation/g4simulation
    ${GSL_INCLUDE_DIRS}
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(g4eval
    phg4hit
    g4detectors
    intt_io
    fun4all
    -L$ENV{OFFLINE_MAIN}/lib
    track_io
    mvtx_io
    calo_io
    CLHEP
    g4jets_io
    g4vertex_io
    trackbase_historic_io
    tpc_io
    micromegas_io
)

install(TARGETS g4eval)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/g4eval/")
