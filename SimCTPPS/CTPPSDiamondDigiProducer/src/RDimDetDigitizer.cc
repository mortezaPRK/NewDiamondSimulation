#include <vector>
#include <iostream>

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimDetDigitizer.h"
#include "Geometry/VeryForwardGeometry/interface/CTPPSPixelTopology.h"

RDimDetDigitizer::RDimDetDigitizer(const edm::ParameterSet &params, CLHEP::HepRandomEngine &eng, uint32_t det_id, const edm::EventSetup &iSetup)
    : params_(params), det_id_(det_id)
{
  verbosity_ = params.getParameter<int>("RDimVerbosity");
  numPixels = CTPPSPixelTopology().detPixelNo();
  theNoiseInElectrons = params.getParameter<double>("RDimEquivalentNoiseCharge");
  thePixelThresholdInE = params.getParameter<double>("RDimDummyROCThreshold");
  noNoise = params.getParameter<bool>("RDimNoNoise");
  //  misalignment_simulation_on_ = params_.getParameter<bool>("RPDisplacementOn");
  _links_persistence = params.getParameter<bool>("CTPPSDiamondDigiSimHitRelationsPersistence");

  // theRPGaussianTailNoiseAdder = new RPGaussianTailNoiseAdder(numStrips,  theNoiseInElectrons, theStripThresholdInE, verbosity_);
  theRDimPileUpSignals = new RDimPileUpSignals(params_, det_id_);
  theRDimDummyROCSimulator = new RDimDummyROCSimulator(params_, det_id_);
  theRDimHitChargeConverter = new RDimHitChargeConverter(params_, eng, det_id_);
  //  theRPDisplacementGenerator = new RPDisplacementGenerator(params_, det_id_, iSetup);
}

RDimDetDigitizer::~RDimDetDigitizer()
{
  // delete theRPGaussianTailNoiseAdder;
  delete theRDimPileUpSignals;
  delete theRDimDummyROCSimulator;
  delete theRDimHitChargeConverter;
  //  delete theRPDisplacementGenerator;
}

void RDimDetDigitizer::run(const std::vector<PSimHit> &input, const std::vector<int> &input_links,
                           std::vector<CTPPSDiamondDigi> &output_digi, //std::vector<RPDetTrigger> &output_trig,
                           std::vector<std::vector<std::pair<int, double>>> &output_digi_links
                           //    ,SimRP::TriggerPrimaryMapType &output_trig_links
)
{
  if (verbosity_)
    std::cout << "RDimDetDigitizer " << det_id_ << " received input.size()=" << input.size() << std::endl;
  theRDimPileUpSignals->reset();

  bool links_persistence_checked = _links_persistence && input_links.size() == input.size();

  int input_size = input.size();
  for (int i = 0; i < input_size; ++i)
  {
    std::map<unsigned short, double, std::less<unsigned short>> the_pixel_charge_map;
    /*    if(misalignment_simulation_on_)
      the_strip_charge_map = theRPHitChargeConverter->processHit(
            theRPDisplacementGenerator->Displace(input[i]));
    else
*/
    the_pixel_charge_map = theRDimHitChargeConverter->processHit(input[i]);

    if (verbosity_)
      std::cout << "RDimHitChargeConverter " << det_id_ << " returned hits=" << the_pixel_charge_map.size() << std::endl;
    if (links_persistence_checked)
      theRDimPileUpSignals->add(the_pixel_charge_map, input_links[i]);
    else
      theRDimPileUpSignals->add(the_pixel_charge_map, 0);
  }

  const std::map<unsigned short, double, std::less<unsigned short>> &theSignal = theRDimPileUpSignals->dumpSignal();
  std::map<unsigned short, std::vector<std::pair<int, double>>> &theSignalProvenance = theRDimPileUpSignals->dumpLinks();
  std::map<unsigned short, double, std::less<unsigned short>> afterNoise;
  //  if(noNoise)
  afterNoise = theSignal;
  //  else
  //    afterNoise = theRPGaussianTailNoiseAdder->addNoise(theSignal);

  theRDimDummyROCSimulator->ConvertChargeToHits(afterNoise, theSignalProvenance,
                                                output_digi, output_digi_links);
}
