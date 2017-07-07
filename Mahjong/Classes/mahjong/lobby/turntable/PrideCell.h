#pragma once

#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;

class PrideCell : public Sprite{
public:
	virtual bool init(PrideType propId,int propNum);
	static PrideCell* create(PrideType propId, int propNum);
    CC_SYNTHESIZE(PrideType, propId, PropId);
    CC_SYNTHESIZE(int, propNum, PropNum)
private:
	std::string getImageNameById(PrideType id);
    
};
