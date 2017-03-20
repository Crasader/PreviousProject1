#pragma once
#include "cocos2d.h"
USING_NS_CC;

class BatteryInfo : public cocos2d::Node {
public:
    
	CREATE_FUNC(BatteryInfo);
private:
	virtual bool init();
	void updateInfo(float delta);
private:
	Label* timerLabel;
	Sprite* batteryItem;
	Sprite* wifiInfo;
};
