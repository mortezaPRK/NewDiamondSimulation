#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "EventFilter/CTPPSRawToDigi/plugins/CTPPSPixelDigiToRaw.h"
#include "EventFilter/CTPPSRawToDigi/plugins/CTPPSDiamondDigiToRaw.h"

DEFINE_FWK_MODULE(CTPPSPixelDigiToRaw);
DEFINE_FWK_MODULE(CTPPSDiamondDigiToRaw);

