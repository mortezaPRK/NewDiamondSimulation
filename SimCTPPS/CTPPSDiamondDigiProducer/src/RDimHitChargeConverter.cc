#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimHitChargeConverter.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimLinearChargeDivider.h"
#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimLinearChargeCollectionDrifter.h"
#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimLinearInduceCharge.h"


RDimHitChargeConverter::RDimHitChargeConverter(const edm::ParameterSet &params, CLHEP::HepRandomEngine& eng, uint32_t det_id)
  : params_(params), det_id_(det_id)
{
  verbosity_ = params.getParameter<int>("RDimVerbosity");
  theRDimChargeDivider = new RDimLinearChargeDivider(params, eng, det_id);
  theRDimChargeCollectionDrifter = new RDimLinearChargeCollectionDrifter(params, det_id);
  theRDimInduceCharge = new RDimLinearInduceCharge(params, det_id);
}

RDimHitChargeConverter::~RDimHitChargeConverter()
{
  delete theRDimChargeDivider;
  delete theRDimChargeCollectionDrifter;
  delete theRDimInduceCharge;
}


std::map<unsigned short, double, std::less<unsigned short> > RDimHitChargeConverter::processHit(const PSimHit &hit)
{  
  std::vector<RDimEnergyDepositUnit> ions_along_path = theRDimChargeDivider->divide(hit);
  if(verbosity_)
    std::cout<<"HitChargeConverter "<<det_id_<<" clouds no generated on the path="<<ions_along_path.size()<<std::endl;
  return theRDimInduceCharge->Induce(theRDimChargeCollectionDrifter->Drift(ions_along_path));
}

