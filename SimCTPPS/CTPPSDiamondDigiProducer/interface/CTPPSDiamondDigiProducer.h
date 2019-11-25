#ifndef SimCTPPS_CTPPSDigiProducer_CTPPSDiamondDigiProducer_h
#define SimCTPPS_CTPPSDigiProducer_CTPPSDiamondDigiProducer_h

// -*- C++ -*-
//
// Package:    CTPPSDiamondDigiProducer
// Class:      CTPPSDiamondDigiProducer
//
/**\class CTPPSDiamondDigiProducer CTPPSDiamondDigiProducer.cc SimCTPPS/CTPPSDiamondDigiProducer/src/CTPPSDiamondDigiProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  F.Ferro
// From TOTEM RPDigiProducer
//

#include "boost/shared_ptr.hpp"

#include <memory>
#include <vector>
#include <map>
#include <string>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"
// #include "DataFormats/CTPPSDigi/interface/CTPPSPixelDigiCollection.h" // TODO: not found in CMS

#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimDetDigitizer.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"

#include "DataFormats/Common/interface/DetSet.h"

//
// class decleration
//

namespace CLHEP
{
class HepRandomEngine;
}

class CTPPSDiamondDigiProducer : public edm::EDProducer
{
public:
   explicit CTPPSDiamondDigiProducer(const edm::ParameterSet &);
   ~CTPPSDiamondDigiProducer();

private:
   virtual void beginRun(edm::Run &, edm::EventSetup const &);
   virtual void produce(edm::Event &, const edm::EventSetup &);
   virtual void endJob();

   std::vector<std::string> RDim_hit_containers_;
   typedef std::map<unsigned int, std::vector<PSimHit>> simhit_map;
   typedef simhit_map::iterator simhit_map_iterator;
   simhit_map SimHitMap;

   edm::ParameterSet conf_;

   std::map<uint32_t, boost::shared_ptr<RDimDetDigitizer>> theAlgoMap;

   std::vector<edm::DetSet<CTPPSDiamondDigi>> theDigiVector;

   CLHEP::HepRandomEngine *rndEngine = nullptr;
   int verbosity_;
   edm::EDGetTokenT<CrossingFrame<PSimHit>> tokenCrossingFrameCTPPSDiamond;
};

#endif
