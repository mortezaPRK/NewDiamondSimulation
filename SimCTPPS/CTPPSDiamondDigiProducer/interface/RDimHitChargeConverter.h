#ifndef SimCTPPS_CTPPSDiamondDigiProducer_RDim_HIT_CHARGE_CONVERTER_H
#define SimCTPPS_CTPPSDiamondDigiProducer_RDim_HIT_CHARGE_CONVERTER_H

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include <map>
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimLinearChargeCollectionDrifter.h"
#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimLinearChargeDivider.h"
#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimLinearInduceCharge.h"

class RDimHitChargeConverter
{
public:
  RDimHitChargeConverter(const edm::ParameterSet &params_, CLHEP::HepRandomEngine &eng, uint32_t det_id);
  ~RDimHitChargeConverter();

  std::map<unsigned short, double, std::less<unsigned short>> processHit(const PSimHit &hit);

private:
  const edm::ParameterSet &params_;
  const uint32_t det_id_;

  RDimLinearChargeDivider *theRDimChargeDivider;
  RDimLinearChargeCollectionDrifter *theRDimChargeCollectionDrifter;
  RDimLinearInduceCharge *theRDimInduceCharge;
  int verbosity_;
};

#endif
