#ifndef SimCTPPS_CTPPSDiamondDigiProducer_LINEAR_CHARGE_DIVIDER_H
#define SimCTPPS_CTPPSDiamondDigiProducer_LINEAR_CHARGE_DIVIDER_H

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimTracker/Common/interface/SiG4UniversalFluctuation.h"
#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimEnergyDepositUnit.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

namespace CLHEP
{
class HepRandomEngine;
}

class RDimLinearChargeDivider
{
public:
  RDimLinearChargeDivider(const edm::ParameterSet &params, CLHEP::HepRandomEngine &eng, uint32_t det_id);
  ~RDimLinearChargeDivider();
  std::vector<RDimEnergyDepositUnit> divide(const PSimHit &hit);

private:
  const edm::ParameterSet &params_;
  CLHEP::HepRandomEngine &rndEngine;
  uint32_t _det_id;

  bool fluctuateCharge_;
  int chargedivisions_;
  double deltaCut_;
  double pitch_;
  double thickness_;
  std::vector<RDimEnergyDepositUnit> the_energy_path_distribution_;
  SiG4UniversalFluctuation *fluctuate;
  int verbosity_;

  void FluctuateEloss(
      int pid, double particleMomentum,
      double eloss, double length, int NumberOfSegs,
      std::vector<RDimEnergyDepositUnit> &elossVector);
};

#endif
