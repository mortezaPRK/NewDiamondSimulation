import FWCore.ParameterSet.Config as cms

ctppsDiamondDAQMappingESSourceXML = cms.ESSource(
    "CTPPSDiamondDAQMappingESSourceXML",
    verbosity=cms.untracked.uint32(2),
    subSystem=cms.untracked.string("RDim"),
    configuration=cms.VPSet(
        # example configuration block:
        cms.PSet(
            validityRange=cms.EventRange("1:min - 999999999:max"),
            mappingFileNames=cms.vstring(
                "CondFormats/CTPPSReadoutObjects/xml/rdim_mapping_220_far.xml"),
            maskFileNames=cms.vstring(
                "CondFormats/CTPPSReadoutObjects/xml/rdim_channel_mask_220_far.xml")
        )
    )
)
