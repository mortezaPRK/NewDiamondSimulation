#ifndef CTPPS_CTPPSDiamondRawToDigi_CTPPSDiamondRawToDigi_h
#define CTPPS_CTPPSDiamondRawToDigi_CTPPSDiamondRawToDigi_h

/** \class CTPPSDiamondRawToDigi_H
 *  Plug-in module that performs Raw data to digi conversion 
 *  for CTPPS pixel detector
 */
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESWatcher.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


#include "CondFormats/DataRecord/interface/CTPPSDiamondDAQMappingRcd.h"
#include "CondFormats/CTPPSReadoutObjects/interface/CTPPSDiamondDAQMapping.h"

#include "DataFormats/FEDRawData/interface/FEDRawDataCollection.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"



class CTPPSDiamondRawToDigi : public edm::stream::EDProducer<> {
public:

  explicit CTPPSDiamondRawToDigi( const edm::ParameterSet& );

  virtual ~CTPPSDiamondRawToDigi();

  /// get data, convert to digis attach againe to Event
  virtual void produce( edm::Event&, const edm::EventSetup& ) override;

private:

  edm::ParameterSet config_;

  edm::EDGetTokenT<FEDRawDataCollection> FEDRawDataCollection_; 

  std::set<unsigned int> fedIds_;

  edm::InputTag label_;
 
  std::string mappingLabel_;
};
#endif
