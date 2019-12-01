#ifndef CTPPSDiamondDigiToRaw_H
#define CTPPSDiamondDigiToRaw_H

/** \class CTPPSDiamondDigiToRaw_H
 */

#include "FWCore/Framework/interface/ESWatcher.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
// #include "CondFormats/DataRecord/interface/CTPPSDiamondDAQMappingRcd.h"
#include "CondFormats/CTPPSReadoutObjects/interface/CTPPSDiamondDAQMapping.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"
#include "CondFormats/CTPPSReadoutObjects/interface/CTPPSDiamondFramePosition.h"


class CTPPSDiamondDigiToRaw final : public edm::EDProducer {
public:

  /// ctor
  explicit CTPPSDiamondDigiToRaw( const edm::ParameterSet& );

  /// dtor
  virtual ~CTPPSDiamondDigiToRaw();


  /// dummy end of job 
  virtual void endJob() override {}

  /// get data, convert to raw event, attach again to Event
  virtual void produce( edm::Event&, const edm::EventSetup& ) override;
typedef uint64_t Word64;

private:
  edm::ParameterSet config_;
  unsigned long eventCounter;
  std::set<unsigned int> fedIds_;
  edm::InputTag label_;  //label of input digi data
  int allDigiCounter;
  int allWordCounter;
  // edm::ESWatcher<CTPPSDiamondDAQMappingRcd> recordWatcher;
  bool debug;
  edm::EDGetTokenT<edm::DetSetVector<CTPPSDiamondDigi>> tCTPPSDiamondDigi; 
  std::map< std::map<const uint32_t, short unsigned int> ,  std::map<short unsigned int, short unsigned int>  > iDdet2fed_;
  CTPPSDiamondFramePosition fPos_;

};
#endif
