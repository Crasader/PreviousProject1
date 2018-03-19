#pragma once

#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;

class PrideCell : public Sprite{
public:
    virtual bool init(PrideType propId,std::string propNum);
	static PrideCell* create(PrideType propId, std::string propNum);
    CC_SYNTHESIZE(PrideType, propId, PropId);
    CC_SYNTHESIZE(std::string, propNum, PropNum)
private:
	std::string getImageNameById(PrideType id);
    
};
