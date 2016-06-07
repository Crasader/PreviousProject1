#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ChangePassword :public Layer, public EditBoxDelegate{
public:
	virtual bool init();
	void onEnter() override;
	void onExit() override;
	CREATE_FUNC(ChangePassword);
private:
	EditBox* _newPassword;
	EditBox* _confirmPassword;
	EventListenerCustom* changePwdListener;
    EventListenerCustom* closeDialogListener;
	Sprite* password_hint_info1;
	Sprite* password_hint_info2;
    std::string newPassword;
    
	void showDialog();
	void changePassword();
	void updateSecond(float dt);
	bool checkPassword(std::string string);
	
	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
	
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
};