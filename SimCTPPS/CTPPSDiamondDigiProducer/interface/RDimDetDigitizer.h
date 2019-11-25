#ifndef SimCTPPS_CTPPSDiamondDigiProducer_RDim_DET_DIGITIZER_H
#define SimCTPPS_CTPPSDiamondDigiProducer_RDim_DET_DIGITIZER_H

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include <vector>
#include <string>

#include "SimTracker/Common/interface/SiG4UniversalFluctuation.h"
#include "SimGeneral/NoiseGenerators/interface/GaussianTailNoiseGenerator.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimHitChargeConverter.h"
#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimDummyROCSimulator.h"
#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"
// #include "DataFormats/CTPPSDigi/interface/CTPPSPixelDigiCollection.h" // TODO: not found in CMS
#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimPileUpSignals.h"

namespace CLHEP
{
class HepRandomEngine;
}

class RDimDetDigitizer
{
public:
  RDimDetDigitizer(const edm::ParameterSet &params, CLHEP::HepRandomEngine &eng, uint32_t det_id, const edm::EventSetup &iSetup);
  void run(const std::vector<PSimHit> &input, const std::vector<int> &input_links,
           std::vector<CTPPSDiamondDigi> &output_digi,
           std::vector<std::vector<std::pair<int, double>>> &output_digi_links);
  ~RDimDetDigitizer();

private:
  RDimPileUpSignals *theRDimPileUpSignals;
  RDimHitChargeConverter *theRDimHitChargeConverter;
  RDimDummyROCSimulator *theRDimDummyROCSimulator;

private:
  const edm::ParameterSet &params_;

  int numPixels;
  double theNoiseInElectrons;
  double thePixelThresholdInE;
  bool noNoise;
  uint32_t det_id_;
  bool misalignment_simulation_on_;
  int verbosity_;
  bool _links_persistence;
};

#endif
