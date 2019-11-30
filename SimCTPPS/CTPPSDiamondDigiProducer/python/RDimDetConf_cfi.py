import FWCore.ParameterSet.Config as cms

RDimDetDigitizer = cms.EDProducer(
    "CTPPSDiamondDigiProducer",

    # all distances in [mm]
    # RPDigiProducer
    ROUList=cms.vstring('CTPPSTimingHits'),
    RDimVerbosity=cms.int32(0),
    # save links betweend digi, clusters and OSCAR/Geant4 hits
    CTPPSDiamondDigiSimHitRelationsPersistence=cms.bool(False),

    # RPDetDigitizer
    RDimEquivalentNoiseCharge=cms.double(1000.0),
    RDimNoNoise=cms.bool(False),

    # RPDisplacementGenerator
    #  RPDisplacementOn = cms.bool(False),

    # RPLinearChargeCollectionDrifter
    RDimGeVPerElectron=cms.double(3.61e-09),
    RDimInterSmearing=cms.vdouble(0.011),

    # RPLinearChargeDivider
    RDimLandauFluctuations=cms.bool(True),
    #   RPChargeDivisionsPerStrip = cms.int32(15),
    #   RPChargeDivisionsPerThickness = cms.int32(5),
    RDimChargeDivisions=cms.int32(20),
    RDimDeltaProductionCut=cms.double(0.120425),    # [MeV]

    # RDimLinearInduceCharge
    #    ChargeMapFile = cms.string("/afs/cern.ch/user/n/nogima/CMSSW_7_5_0/src/CNM_CT_PPS_10_4_ChargeMap_Angle_0_norm.root"),
    ChargeMapFile=cms.string("CNM_CT_PPS_10_4_ChargeMap_Angle_0_norm.root"),
    # fraction of the remaining charge going to the closer neighbour pixel. Value = 0.135, Value = 0.0 bypass the charge map and the charge sharing approach
    RDimCoupling=cms.double(0.135),

    # RDimDummyROCSimulator

    #  RDimDummyROCThreshold = cms.double(2500.0),
    RDimDummyROCThreshold=cms.double(1900.0),
    RDimDummyROCElectronPerADC=cms.double(210.0),   # 210.0 to be verified
    RDimDeadDiamondProbability=cms.double(0.001),
    RDimDeadDiamondSimulationOn=cms.bool(False),

    # CTPPSDiamondSimTopology
    #   RPSharingSigmas = cms.double(5.0), # how many sigmas taken into account for the edges and inter strips
    #  RPTopEdgeSmearing = cms.double(0.011),
    #  RPBottomEdgeSmearing = cms.double(0.011),
    RDimActiveEdgeSmearing=cms.double(0.020),
    RDimActiveEdgePosition=cms.double(0.150),   # from the physical edge
    #   RPTopEdgePosition = cms.double(1.5),
    #  RPBottomEdgePosition = cms.double(1.5)

    mixLabel=cms.string("mix"),
    InputCollection=cms.string("g4SimHitsCTPPSDiamondHits") #### TODO: check this later
)
