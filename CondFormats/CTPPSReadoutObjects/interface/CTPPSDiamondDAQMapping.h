/****************************************************************************
 *
 * 
 * Authors: 
 *   F.Ferro ferro@ge.infn.it
 *
 ****************************************************************************/

#ifndef CondFormats_CTPPSReadoutObjects_CTPPSDiamondDAQMapping
#define CondFormats_CTPPSReadoutObjects_CTPPSDiamondDAQMapping

#include "CondFormats/Serialization/interface/Serializable.h"
#include "CondFormats/CTPPSReadoutObjects/interface/CTPPSDiamondFramePosition.h"
#include "CondFormats/CTPPSReadoutObjects/interface/CTPPSDiamondIndices.h"

#include <map>
#include <set>

//----------------------------------------------------------------------------------------------------

/**
 *\brief Contains mappind data related to a ROC.
 */
class CTPPSDiamondROCInfo
{
public:
  /// the symbolic id
  uint32_t iD;

  unsigned int roc;
    
  friend std::ostream& operator << (std::ostream& s, const CTPPSDiamondROCInfo &fp);

  COND_SERIALIZABLE;
};

//----------------------------------------------------------------------------------------------------

/**
 *\brief The mapping between FramePosition and ROCInfo.
 */
class CTPPSDiamondDAQMapping
{
public:
  std::map<CTPPSDiamondFramePosition, CTPPSDiamondROCInfo> ROCMapping;
    
  void insert(const CTPPSDiamondFramePosition &fp, const CTPPSDiamondROCInfo &vi);

  std::set<unsigned int> fedIds() const;

  COND_SERIALIZABLE;

};

#endif
