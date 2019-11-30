
#include "SimCTPPS/CTPPSDiamondDigiProducer/interface/RDimPileUpSignals.h"
#include <iostream>


RDimPileUpSignals::RDimPileUpSignals(const edm::ParameterSet & params, uint32_t det_id)
 : det_id_(det_id)
{
  links_persistence_ = params.getParameter<bool>("CTPPSDiamondDigiSimHitRelationsPersistence");
  verbosity_ = params.getParameter<int>("RDimVerbosity");
}

void RDimPileUpSignals::reset()
{
  the_pixel_charge_piled_up_map_.clear();
  the_pixel_charge_piled_up_map_links_.clear();
}

void RDimPileUpSignals::add(const std::map<unsigned short, double, std::less<unsigned short> > &charge_induced, int PSimHitIndex)
{
  for(std::map<unsigned short, double, std::less<unsigned short> >::const_iterator i=charge_induced.begin();
      i!=charge_induced.end(); ++i)
  {
    the_pixel_charge_piled_up_map_[i->first]+=i->second;
    if(links_persistence_ && i->second>0)
    {
      the_pixel_charge_piled_up_map_links_[i->first].push_back(std::pair<int, double>(PSimHitIndex, i->second));
      if(verbosity_)
      {
        std::cout<<"Det id="<<det_id_<<" pixel="<<i->first<<" charge="<<i->second<<std::endl;
      }
    }
  }
}
