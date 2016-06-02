#pragma once

#include "cocos2d.h"
#include "game/mahjong/state/GameData.h"
USING_NS_CC;

class PrideCell : public Sprite{
public:
	virtual bool init(PrideType propId,int propNum);
	static PrideCell* create(PrideType propId, int propNum);
private:
	std::string getImageNameById(PrideType id);
};