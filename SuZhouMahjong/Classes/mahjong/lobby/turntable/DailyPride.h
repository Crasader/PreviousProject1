#pragma once

#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;

class DailyPride :public Layer{

public:
	virtual bool init();
	void onEnter() override;
	void onExit() override;
    void onEnterTransitionDidFinish() override;
    void updateData();
	CREATE_FUNC(DailyPride);
	
private:
	EventListenerCustom* prideCallBackListener1;
    EventListenerCustom* prideCallBackListener2;
	Menu* startMenu;
	Sprite* m_turnBg;
	void showDailyPrideLayer();
	void beginPride(Ref* ref);
    void shareTurntable();
    void closeView();
    void showTurntableResult(PrideType type,std::string num);
    void update(float dt) override;
	Point getPosByRotation(Point pos,float r,float a);
    void getTurnTablePride();
    std::string getImageNameById(PrideType id);
};
