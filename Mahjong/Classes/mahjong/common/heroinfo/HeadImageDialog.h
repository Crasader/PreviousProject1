#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class HeadImageDialog :public Layer{
public:
	virtual bool init();
	void onEnter() override;
	void onExit() override;
	CREATE_FUNC(HeadImageDialog);
    CC_SYNTHESIZE(std::string, currentGender, CurrentGender);
private:
	EventListenerCustom* changeImageListener;
	void showDialog();
	void closeView();
	void useCamara();
	void usePhoto();
    void selectedHeadImage(Ref* ref);
    void confirmHead();
    CC_SYNTHESIZE(int , selectId, SelectId);
};