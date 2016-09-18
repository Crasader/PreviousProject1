#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class BoundPhone :public Layer, public EditBoxDelegate{
public:
	virtual bool init();
	void onEnter() override;
	void onExit() override;
	CREATE_FUNC(BoundPhone);
private:
	int totalTime;
	Label* clock;
	EditBox* _phoneNum;
	EditBox* _verification;
	Sprite* hintSprite;
	EventListenerCustom* boundPhoneListener;
    
	void showDialog();
	void getVerification(Ref* ref);
	void updateSecond(float dt);
	void confirmBound();
	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
};