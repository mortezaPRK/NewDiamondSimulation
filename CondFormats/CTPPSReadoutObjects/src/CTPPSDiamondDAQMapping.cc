/****************************************************************************
 *
 * 
 * Authors: 
 * F.Ferro ferro@ge.infn.it
 *
 ****************************************************************************/

#include "FWCore/Utilities/interface/typelookup.h"

#include "CondFormats/CTPPSReadoutObjects/interface/CTPPSDiamondDAQMapping.h"

using namespace std;

//----------------------------------------------------------------------------------------------------

std::set<unsigned int> CTPPSDiamondDAQMapping::fedIds() const {
  std::set<unsigned int> fedSet;
  for (const auto &p : ROCMapping){
    fedSet.insert(p.first.getFEDId() );
  }
  return fedSet;
}

std::ostream& operator << (std::ostream& s, const CTPPSDiamondROCInfo &vi)
{
  s << "ID="<< vi.iD << "  ROC=" << vi.roc;

  return s;
}

//----------------------------------------------------------------------------------------------------

// void CTPPSDiamondDAQMapping::insert(const CTPPSDiamondFramePosition &fp, const CTPPSDiamondROCInfo &vi)
// {
//   auto it = ROCMapping.find(fp);  
//   if (it != ROCMapping.end())
//     {
//       edm::LogError("RDim") << "WARNING in DAQMapping::insert > Overwriting entry at " << fp << ". Previous: " 
// 	   << "    " << ROCMapping[fp] << ","  << "  new: "  << "    " << vi << ". ";
//     }

//   ROCMapping[fp] = vi;
// }
