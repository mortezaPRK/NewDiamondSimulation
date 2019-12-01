/*
 * adapting to CTPPS diamond detector March 2017 - F.Ferro
 */


#include "EventFilter/CTPPSRawToDigi/interface/CTPPSDiamondRawToDigi.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"

#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/FEDRawData/interface/FEDRawDataCollection.h"
#include "DataFormats/FEDRawData/interface/FEDRawData.h"
#include "DataFormats/FEDRawData/interface/FEDNumbering.h"
#include "DataFormats/DetId/interface/DetIdCollection.h"

#include "EventFilter/CTPPSRawToDigi/interface/CTPPSDiamondDataFormatter.h"

#include "FWCore/Framework/interface/ConsumesCollector.h"

using namespace std;


CTPPSDiamondRawToDigi::CTPPSDiamondRawToDigi( const edm::ParameterSet& conf ) 
  : config_(conf)

{

  FEDRawDataCollection_ = consumes <FEDRawDataCollection> (config_.getParameter<edm::InputTag>("InputLabel"));

// Products
  produces< edm::DetSetVector<CTPPSDiamondDigi> >();

//CablingMap could have a label //Tav
  mappingLabel_ = config_.getParameter<std::string> ("mappingLabel"); //RDim

}


CTPPSDiamondRawToDigi::~CTPPSDiamondRawToDigi() {
  edm::LogInfo("CTPPSDiamondRawToDigi")  << " CTPPSDiamondRawToDigi destructor!";

}

void CTPPSDiamondRawToDigi::produce( edm::Event& ev,
				   const edm::EventSetup& es) 
{


  edm::Handle<FEDRawDataCollection> buffers;
  ev.getByToken(FEDRawDataCollection_, buffers);

  edm::ESHandle<CTPPSDiamondDAQMapping> mapping;

  bool data_exist=false;
  for(int fed = FEDNumbering::MINCTPPSDiamondsFEDID; fed <=  FEDNumbering::MAXCTPPSDiamondsFEDID; fed++){
    const FEDRawData& tempRawData = buffers->FEDData( fed );
    if(tempRawData.size()!=0){
      data_exist=true;
      break;
    }
  }
/// create product (digis & errors)
  auto collection = std::make_unique<edm::DetSetVector<CTPPSDiamondDigi>>();


  if(data_exist){
  //es.get<CTPPSDiamondDAQMappingRcd>().get( mapping);
  es.get<CTPPSDiamondDAQMappingRcd>().get(mappingLabel_, mapping);


    fedIds_   = mapping->fedIds();

    CTPPSDiamondDataFormatter formatter(mapping->ROCMapping);
    
    bool errorsInEvent = false; 
    for (auto aFed = fedIds_.begin(); aFed != fedIds_.end(); ++aFed) {
      int fedId = *aFed;
      
      edm::LogInfo("CTPPSDiamondRawToDigi")<< " PRODUCE DIGI FOR FED: " <<  dec <<fedId << endl;
/// get event data for this fed
      const FEDRawData& fedRawData = buffers->FEDData( fedId );
      
      formatter.interpretRawData( errorsInEvent, fedId, fedRawData, *collection);
    }
  }
///send digis and errors back to framework 
  ev.put(std::move(collection));

}

DEFINE_FWK_MODULE( CTPPSDiamondRawToDigi);
