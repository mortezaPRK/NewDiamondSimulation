#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/CTPPSDiamondDigiProducer.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/CrossingFrame/interface/CrossingFrame.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include <cstdlib>

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/Common/interface/DetSetVector.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "CLHEP/Random/RandomEngine.h"

CTPPSDiamondDigiProducer::CTPPSDiamondDigiProducer(const edm::ParameterSet &conf) : conf_(conf)
{
	produces<edm::DetSetVector<CTPPSDiamondDigi>>();
	tokenCrossingFrameCTPPSDiamond = consumes<CrossingFrame<PSimHit>>(edm::InputTag("mix", "g4SimHitsCTPPSDiamondHits"));
	RDim_hit_containers_.clear();
	RDim_hit_containers_ = conf.getParameter<std::vector<std::string>>("ROUList");
	verbosity_ = conf.getParameter<int>("RDimVerbosity");
}

CTPPSDiamondDigiProducer::~CTPPSDiamondDigiProducer()
{
}

void CTPPSDiamondDigiProducer::produce(edm::Event &iEvent, const edm::EventSetup &iSetup)
{
	using namespace edm;
	if (!rndEngine)
	{
		Service<RandomNumberGenerator> rng;
		if (!rng.isAvailable())
		{
			throw cms::Exception("Configuration") << "This class requires the RandomNumberGeneratorService\n"
													 "which is not present in the configuration file.  You must add the service\n"
													 "in the configuration file or remove the modules that require it.";
		}
		rndEngine = &(rng->getEngine(iEvent.streamID()));
	}

	edm::Handle<CrossingFrame<PSimHit>> cf;
	iEvent.getByToken(tokenCrossingFrameCTPPSDiamond, cf);
	if (verbosity_)
	{
		std::cout << "\n\n=================== Starting SimHit access"
				  << "  ===================" << std::endl;

		std::auto_ptr<MixCollection<PSimHit>> col(new MixCollection<PSimHit>(cf.product(), std::pair<int, int>(-0, 0)));
		std::cout << *(col.get()) << std::endl;
		MixCollection<PSimHit>::iterator cfi;
		int count = 0;
		for (cfi = col->begin(); cfi != col->end(); cfi++)
		{
			std::cout << " Hit " << count << " has tof " << cfi->timeOfFlight() << " trackid "
					  << cfi->trackId() << " bunchcr " << cfi.bunch() << " trigger " << cfi.getTrigger()
					  << ", from EncodedEventId: " << cfi->eventId().bunchCrossing() << " "
					  << cfi->eventId().event() << " bcr from MixCol " << cfi.bunch() << std::endl;
			std::cout << " Hit: " << (*cfi) << "  " << cfi->exitPoint() << std::endl;
			count++;
		}
	}

	std::auto_ptr<MixCollection<PSimHit>> allRDimHits(new MixCollection<PSimHit>(cf.product(), std::pair<int, int>(0, 0)));

	if (verbosity_)
		std::cout << "Input MixCollection size = " << allRDimHits->size() << std::endl;

	SimHitMap.clear();

	MixCollection<PSimHit>::iterator isim;
	for (isim = allRDimHits->begin(); isim != allRDimHits->end(); ++isim)
	{
		SimHitMap[(*isim).detUnitId()].push_back((*isim));
	}

	theDigiVector.reserve(400);
	theDigiVector.clear();

	for (simhit_map_iterator it = SimHitMap.begin(); it != SimHitMap.end(); ++it)
	{
		edm::DetSet<CTPPSDiamondDigi> digi_collector(it->first);

		if (theAlgoMap.find(it->first) == theAlgoMap.end())
		{
			theAlgoMap[it->first] = boost::shared_ptr<RDimDetDigitizer>(
				new RDimDetDigitizer(conf_, *rndEngine, it->first, iSetup)); //per ogni rivelatore creo un digitizer
		}

		std::vector<int> input_links;
		std::vector<std::vector<std::pair<int, double>>> output_digi_links; // i links sono i links ai simhits che generano il digi

		(theAlgoMap.find(it->first)->second)->run(SimHitMap[it->first], input_links, digi_collector.data, output_digi_links); // runno il digitizer

		std::vector<CTPPSDiamondDigi>::iterator pixelIterator = digi_collector.data.begin();

		if (digi_collector.data.size() > 0)
		{
			theDigiVector.push_back(digi_collector); // colleziono i digi di tutti i rivelatori
		}
	}

	std::unique_ptr<edm::DetSetVector<CTPPSDiamondDigi>> digi_output(new edm::DetSetVector<CTPPSDiamondDigi>(theDigiVector));

	if (verbosity_)
	{
		std::cout << "digi_output->size()=" << digi_output->size() << std::endl;
	}

	iEvent.put(std::move(digi_output));
}

void CTPPSDiamondDigiProducer::beginRun(edm::Run &, edm::EventSetup const &es)
{
}

void CTPPSDiamondDigiProducer::endJob()
{
}

DEFINE_FWK_MODULE(CTPPSDiamondDigiProducer);
