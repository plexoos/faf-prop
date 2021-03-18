set(libphg4hit_la_SOURCES
  phg4hit_Dict.cxx
  EicEventHeader.cc
  EicEventHeaderv1.cc
  PHG4EventHeaderv1.cc
  PHG4Hit.cc
  PHG4Hitv1.cc
  PHG4HitContainer.cc
  PHG4HitDefs.cc
  PHG4HitEval.cc
  PHG4InEvent.cc
  PHG4Particle.cc
  PHG4Particlev1.cc
  PHG4Particlev2.cc
  PHG4Particlev3.cc
  PHG4Showerv1.cc
  PHG4TruthInfoContainer.cc
  PHG4VtxPoint.cc
  PHG4VtxPointv1.cc
)

set(libg4testbench_la_SOURCES
  Fun4AllMessenger.cc
  G4TBMagneticFieldSetup.cc
  G4TBFieldMessenger.cc
  Fun4AllDstPileupInputManager.cc
  Fun4AllDstPileupMerger.cc
  Fun4AllSingleDstPileupInputManager.cc
  HepMCNodeReader.cc
  PHG4ConsistencyCheck.cc
  PHG4DisplayAction.cc
  PHG4Detector.cc
  PHG4HitReadBack.cc
  PHG4EtaParameterization.cc
  PHG4EtaPhiParameterization.cc
  PHG4HeadReco.cc
  PHG4InEventCompress.cc
  PHG4InEventReadBack.cc
  PHG4InputFilter.cc
  PHG4IonGun.cc
  PHG4MagneticField.cc
  PHG4ParticleGeneratorBase.cc
  PHG4ParticleGenerator.cc
  PHG4ParticleGeneratorVectorMeson.cc
  PHG4ParticleGeneratorD0.cc
  PHG4ParticleGun.cc
  PHG4PhenixDetector.cc
  PHG4PhenixDisplayAction.cc
  PHG4PhenixEventAction.cc
  PHG4PhenixSteppingAction.cc
  PHG4PhenixTrackingAction.cc
  PHG4PileupGenerator.cc
  PHG4PrimaryGeneratorAction.cc
  PHG4Reco.cc
  PHG4RegionInformation.cc
  PHG4ScoringManager.cc
  PHG4SimpleEventGenerator.cc
  PHG4SteppingAction.cc
  PHG4Subsystem.cc
  PHG4TrackUserInfoV1.cc
  PHG4TruthEventAction.cc
  PHG4TruthSubsystem.cc
  PHG4TruthTrackingAction.cc
  PHG4UIsession.cc
  PHG4Utils.cc
  PHG4VertexSelection.cc
  ReadEICFiles.cc
)

root_generate_dictionary(
  phg4hit_Dict
  EicEventHeader.h
  EicEventHeaderv1.h
  PHG4EventHeader.h
  PHG4EventHeaderv1.h
  PHG4Hit.h
  PHG4Hitv1.h
  PHG4HitEval.h
  PHG4HitContainer.h
  PHG4InEvent.h
  PHG4Particle.h
  PHG4Particlev1.h
  PHG4Particlev2.h
  PHG4Particlev3.h
  PHG4Shower.h
  PHG4Showerv1.h
  PHG4VtxPoint.h
  PHG4VtxPointv1.h
  PHG4TruthInfoContainer.h
  MODULE phg4hit
  LINKDEF LinkDef.h
  OPTIONS -I${CMAKE_CURRENT_SOURCE_DIR}
)

set(pkginclude_HEADERS
  EicEventHeader.h
  Fun4AllDstPileupInputManager.h
  Fun4AllDstPileupMerger.h
  Fun4AllSingleDstPileupInputManager.h
  HepMCNodeReader.h
  PHBBox.h
  PHG4ColorDefs.h
  PHG4Detector.h
  PHG4DisplayAction.h
  PHG4EventAction.h
  PHG4EventHeader.h
  PHG4HitDefs.h
  PHG4Hit.h
  PHG4Hitv1.h
  PHG4HitEval.h
  PHG4HitContainer.h
  PHG4InEvent.h
  PHG4IonGun.h
  PHG4Particle.h
  PHG4Particlev1.h
  PHG4Particlev2.h
  PHG4Particlev3.h
  PHG4ParticleGenerator.h
  PHG4ParticleGeneratorBase.h
  PHG4ParticleGeneratorD0.h
  PHG4ParticleGeneratorVectorMeson.h
  PHG4ParticleGun.h
  PHG4PhenixDetector.h
  PHG4PileupGenerator.h
  PHG4PrimaryGeneratorAction.h
  PHG4Reco.h
  PHG4RegionInformation.h
  PHG4ScoringManager.h
  PHG4SimpleEventGenerator.h
  PHG4Shower.h
  PHG4Showerv1.h
  PHG4SteppingAction.h
  PHG4Subsystem.h
  PHG4TrackingAction.h
  PHG4TrackUserInfoV1.h
  PHG4TruthInfoContainer.h
  PHG4TruthSubsystem.h
  PHG4Units.h
  PHG4Utils.h
  PHG4VertexSelection.h
  PHG4VtxPoint.h
  PHG4VtxPointv1.h
  ReadEICFiles.h
)

add_library(phg4hit ${libphg4hit_la_SOURCES})
add_library(g4testbench ${libg4testbench_la_SOURCES})

set_target_properties(phg4hit PROPERTIES SOVERSION 0)
set_target_properties(g4testbench PROPERTIES SOVERSION 0)

target_include_directories(phg4hit
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${ROOT_INCLUDE_DIRS}
    $ENV{OFFLINE_MAIN}/include
    $ENV{G4_MAIN}/include
)

target_include_directories(g4testbench
    PRIVATE
    ${CMAKE_SOURCE_DIR}/offline/framework
    ${CMAKE_SOURCE_DIR}/generators
    ${ROOT_INCLUDE_DIRS}
    $ENV{OFFLINE_MAIN}/include
    $ENV{OFFLINE_MAIN}/include/eigen3
    $ENV{G4_MAIN}/include
)

target_link_libraries(g4testbench phg4hit
    ${Boost_FILESYSTEM_LIBRARY}
    ${Geant4_LIBRARIES}
    fun4all
    -L$ENV{OFFLINE_MAIN}/lib
    EICPhysicsList eicsmear g4decayer gsl gslcblas HepMC phfield phgeom
    phg4gdml phhepmc phparameter vararray
)

install(TARGETS phg4hit g4testbench)
install(FILES ${pkginclude_HEADERS} DESTINATION "include/g4main/")
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/libphg4hit_rdict.pcm
    ${CMAKE_CURRENT_BINARY_DIR}/libphg4hit.rootmap
    DESTINATION "lib/")
