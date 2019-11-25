#ifndef SimPPS_CTPPSDiamondDigiProducer_RDim_LINEAR_INDUCE_CHARGE_H
#define SimPPS_CTPPSDiamondDigiProducer_RDim_LINEAR_INDUCE_CHARGE_H

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <vector>
// #include "Geometry/VeryForwardGeometry/interface/CTPPSPixelSimTopology.h" // TODO: not found in CMS
#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimSignalPoint.h"

class TFile;
class TH2D;
class RDimLinearInduceCharge
{
public:
  RDimLinearInduceCharge(const edm::ParameterSet &params, uint32_t det_id);
  std::map<unsigned short, double, std::less<unsigned short>> Induce(const std::vector<RDimSignalPoint> &charge_map);

private:
  uint32_t det_id_;
  std::vector<double> signalCoupling_;
  std::map<unsigned short, double, std::less<unsigned short>> theDiamondChargeMap;
  // CTPPSPixelSimTopology theRPixDetTopology_; // TODO: not found in CMS
  double sqrt_2;
  int no_of_pixels_;
  int verbosity_;
  std::string ChargeMapFile_;
  TFile *fChargeMap;
  TH2D *hChargeMap;
};

#endif
