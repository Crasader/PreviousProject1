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
	void getVerification();
	void updateSecond(float dt);
	void confirmBound();
	bool checkPhone(std::string phone);
	//��ʼ����༭
	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	//�����༭
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	//�༭���ı��ı�
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
	//������return��Ļص�����
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
};