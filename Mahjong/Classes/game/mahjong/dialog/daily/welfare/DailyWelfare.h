#pragma once

#include "cocos2d.h"
USING_NS_CC;

class DailyWelfare :public Layer{
public :
	virtual bool init();
	CREATE_FUNC(DailyWelfare);
private:
	void showDailyWelfareLayer();
	void recievePride(Ref* ref);

};