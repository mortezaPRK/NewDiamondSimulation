#ifndef SimCTPPS_RDIMDigiAnalyzer_h
#define SimCTPPS_RDIMDigiAnalyzer_h

#include "FWCore/Framework/interface/ConsumesCollector.h"

#include <FWCore/Framework/interface/EDAnalyzer.h>
#include <DataFormats/CTPPSDetId/interface/CTPPSDiamondDetId.h>
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"
// #include "DataFormats/CTPPSDigi/interface/CTPPSPixelDigiCollection.h" // TODO: not found in CMS

#include "SimDataFormats/CrossingFrame/interface/CrossingFrame.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/DetSetVector.h"

// #include "Geometry/VeryForwardGeometry/interface/CTPPSPixelSimTopology.h" // TODO: not found in CMS 
#include "TH2D.h"

class TH1F;
class TFile;
class PSimHit;

namespace edm
{
class ParameterSet;
class Event;
class EventSetup;
} // namespace edm

class CTPPSDiamondDigiAnalyzer : public edm::EDAnalyzer
{

public:
  explicit CTPPSDiamondDigiAnalyzer(const edm::ParameterSet &pset);
  virtual ~CTPPSDiamondDigiAnalyzer();
  void endJob();
  void beginJob();
  void analyze(const edm::Event &event, const edm::EventSetup &eventSetup);

private:

  TH2D *hAllHits;
  TH2D *hOneHitperEvent;
  TH2D *hOneHitperEvent2;
  TH2D *hOneHitperEventCenter;
  TH2D *hOneHitperEvent2Center;
  TFile *file;
  std::string label;

  int verbosity_;
  edm::EDGetTokenT<edm::PSimHitContainer> psim_token;
  edm::EDGetTokenT<edm::DetSetVector<CTPPSDiamondDigi>> pixel_token;

  // CTPPSPixelSimTopology theRPixDetTopology_; // TODO: not found in CMS
  unsigned int found_corresponding_digi_count;
  unsigned int cumulative_cluster_size[3];
};

#endif
