#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimLinearChargeCollectionDrifter.h"
#include "Geometry/VeryForwardGeometry/interface/CTPPSPixelTopology.h"
#include <iostream>
#include <vector>

RDimLinearChargeCollectionDrifter::RDimLinearChargeCollectionDrifter
      (const edm::ParameterSet &params, uint32_t det_id)
{
  verbosity_ = params.getParameter<int>("RDimVerbosity");
  //charge_cloud_sigma_ = params.getParameter<double>("RDimInterStripSmearing");
  GeV_per_electron_ = params.getParameter<double>("RDimGeVPerElectron");
  charge_cloud_sigmas_vect_ = params.getParameter< std::vector<double> >("RDimInterSmearing");
  det_thickness_ = CTPPSPixelTopology().detThickness();
  _det_id=det_id;
}

std::vector<RDimSignalPoint> RDimLinearChargeCollectionDrifter::Drift
      (const std::vector<RDimEnergyDepositUnit> &energy_deposition)
{
  _temp.resize(energy_deposition.size());
  for(unsigned int i=0; i<energy_deposition.size(); i++)
  {
    _temp[i].Position() = LocalPoint(energy_deposition[i].X(), energy_deposition[i].Y());
// alla fine sigma e' solo un numero (o un set di numeri) dati nel .py. Per le strips e' 0.011
    _temp[i].Sigma() = GetSigma(energy_deposition[i].Z());  //befor charge_cloud_sigma_ used, now a vector of sigmas;
    _temp[i].Charge() = energy_deposition[i].Energy()/GeV_per_electron_;
    if(verbosity_)
    {
      std::cout<<"RDimLinearChargeCollectionDrifter "<<_det_id<<" :"<<_temp[i].Position()<<" "
        <<_temp[i].Sigma()<<" "<<_temp[i].Charge()<<std::endl;
    }
  }
  return _temp;
}
