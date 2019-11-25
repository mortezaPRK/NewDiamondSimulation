#ifndef RDIM_DUMMY_ROC_SIMULATION_H
#define RDIM_DUMMY_ROC_SIMULATION_H

#include <set>

#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"
// #include "DataFormats/CTPPSDigi/interface/CTPPSPixelDigiCollection.h" // TODO: not found in CMS
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class RDimDummyROCSimulator
{
public:
  RDimDummyROCSimulator(const edm::ParameterSet &params, uint32_t det_id);
  void ConvertChargeToHits(
      const std::map<unsigned short, double, std::less<unsigned short>> &signals,
      std::map<unsigned short, std::vector<std::pair<int, double>>> &theSignalProvenance,
      std::vector<CTPPSDiamondDigi> &output_digi,
      std::vector<std::vector<std::pair<int, double>>> &output_digi_links);

private:
  typedef std::set<unsigned short, std::less<unsigned short>> dead_pixel_set;
  void SetDeadPixels();
  const edm::ParameterSet &params_;
  uint32_t det_id_;
  double dead_pixel_probability_;
  bool dead_pixels_simulation_on_;
  dead_pixel_set dead_pixels_;
  int verbosity_;

  unsigned short pixels_no_;
  double threshold_;
  double electron_per_adc_;
  bool links_persistence_;
};

#endif
