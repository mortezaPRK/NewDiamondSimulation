#include "CTPPSTotemDigiToRaw.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/CTPPSDigi/interface/TotemRPDigi.h"
#include "DataFormats/FEDRawData/interface/FEDRawDataCollection.h"
#include "DataFormats/FEDRawData/interface/FEDRawData.h"

#include "CondFormats/CTPPSReadoutObjects/interface/TotemDAQMapping.h"
#include "CondFormats/DataRecord/interface/TotemReadoutRcd.h"

#include "EventFilter/CTPPSRawToDigi/interface/CTPPSTotemDataFormatter.h"

//raw test
#include "DataFormats/DetId/interface/DetIdCollection.h"
#include "DataFormats/FEDRawData/interface/FEDNumbering.h"
#include "EventFilter/CTPPSRawToDigi/interface/CTPPSPixelRawToDigi.h"

using namespace std;

CTPPSTotemDigiToRaw::CTPPSTotemDigiToRaw( const edm::ParameterSet& pset ) :
  config_(pset)
{

  tTotemRPDigi = consumes<edm::DetSetVector<TotemRPDigi> >(config_.getParameter<edm::InputTag>("InputLabel")); 

  // Define EDProduct type
  produces<FEDRawDataCollection>();

  // start the counters
  eventCounter = 0;
  allDigiCounter = 0;
  allWordCounter = 0;

}

// -----------------------------------------------------------------------------
CTPPSTotemDigiToRaw::~CTPPSTotemDigiToRaw() {
  edm::LogInfo("CTPPSTotemDigiToRaw")  << " CTPPSTotemDigiToRaw destructor!";

}

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void CTPPSTotemDigiToRaw::produce( edm::Event& ev,
                              const edm::EventSetup& es)
{
  eventCounter++;
  edm::LogInfo("CTPPSTotemDigiToRaw") << "[CTPPSTotemDigiToRaw::produce] "
                                   << "event number: " << eventCounter;

  edm::Handle< edm::DetSetVector<TotemRPDigi> > digiCollection;
  label_ = config_.getParameter<edm::InputTag>("InputLabel");
  ev.getByToken( tTotemRPDigi, digiCollection);

//  CTPPSTotemDataFormatter::RawData rawdata;
  CTPPSTotemDataFormatter::Digis digis;

  //typedef edm::DetSet<TotemRPDigi>::const_iterator DI;
  int digiCounter = 0; 
  typedef vector< edm::DetSet<TotemRPDigi> >::const_iterator DI;
  for (DI di=digiCollection->begin(); di != digiCollection->end(); di++) {
	 digiCounter += (di->data).size();
    std::cout << "print digi size =  "  <<  (di->data).size() <<  std::endl;
    std::cout << "detId strip =  "  <<  di->detId() <<  std::endl;
    digis[ di->detId()] = di->data;
     for (edm::DetSet<TotemRPDigi>::const_iterator dit = di->begin(); dit != di->end(); ++dit) {
	std::cout << " strip number  =  " << dit->getStripNumber() << std::endl;
	}
  }
  allDigiCounter += digiCounter;
    std::cout << "print all digi size =  "  <<  allDigiCounter << std::endl; 
  edm::ESHandle<TotemDAQMapping> mapping;
  if (recordWatcher.check( es )) {
    es.get<TotemReadoutRcd>().get(mapping);

    std::cout << " recordWatcher TotemReadoutRcd "  << std::endl; 
    }
/*
    es.get<TotemReadoutRcd>().get("RPix",mapping);
    for (const auto &p : mapping->ROCMapping)    {
        const uint32_t piD = p.second.iD;  
        short unsigned int pROC   = p.second.roc;
        short unsigned int pFediD = p.first.getFEDId();
        short unsigned int pFedcH = p.first.getChannelIdx();
	 
	std::map<const uint32_t,short unsigned int> mapDetRoc; 
        mapDetRoc.insert(std::pair<const uint32_t,short unsigned int>(piD,pROC)); 
	std::map<short unsigned int,short unsigned int> mapFedIdCh; 
        mapFedIdCh.insert(std::pair<short unsigned int,short unsigned int>(pFediD,pFedcH)); 

	iDdet2fed_.insert(std::pair<std::map<const uint32_t,short unsigned int> ,std::map<short unsigned int,short unsigned int>>(mapDetRoc,mapFedIdCh));
    }
    fedIds_ = mapping->fedIds();
  }
  //debug = edm::MessageDrop::instance()->debugEnabled;


  CTPPSTotemDataFormatter formatter(mapping->ROCMapping);

  // create product (raw data)
  auto buffers = std::make_unique<FEDRawDataCollection>();

  // convert data to raw
  //if(digis.size() != 0 )

  formatter.formatRawData( ev.id().event(), rawdata, digis, iDdet2fed_);
  bool data_exist = false; 
  // pack raw data into collection
  for (auto it = fedIds_.begin(); it != fedIds_.end(); it++) { 
    FEDRawData& fedRawData = buffers->FEDData( *it );
    CTPPSTotemDataFormatter::RawData::iterator fedbuffer = rawdata.find( *it );
    if( fedbuffer != rawdata.end() ) fedRawData = fedbuffer->second;

    int nWords = fedRawData.size()/sizeof(Word64);
    if (nWords!=0) data_exist = true; 
  }
  if(data_exist) { 
	allWordCounter += formatter.nWords();

	if (debug) LogDebug("CTPPSTotemDigiToRaw") 
	        << "Words/Digis this ev: "<<digiCounter<<"(fm:"<<formatter.nDigis()<<")/"
        	<<formatter.nWords()
	        <<"  all: "<< allDigiCounter <<"/"<<allWordCounter;

	ev.put(std::move(buffers));
  }
*/
}
