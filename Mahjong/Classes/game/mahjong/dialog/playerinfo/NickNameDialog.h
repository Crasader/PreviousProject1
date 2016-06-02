#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class NickNameDialog :public Layer, public EditBoxDelegate{
public:
	virtual bool init();
	void onEnter() override;
	void onExit() override;
	CREATE_FUNC(NickNameDialog);
private:
	EditBox* _editName;
	Sprite* nickNameHintInfo;
	EventListenerCustom* checkNickName;
	EventListenerCustom* changeNicknameListener;
	void showDialog();
	void closeView();
	void clearInput();
	void changeNickName();
	//开始进入编辑
	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	//结束编辑
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	//编辑框文本改变
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
	//当触发return后的回调函数
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
};