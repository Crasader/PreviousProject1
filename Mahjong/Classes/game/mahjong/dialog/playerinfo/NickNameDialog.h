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
	//��ʼ����༭
	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	//�����༭
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	//�༭���ı��ı�
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
	//������return��Ļص�����
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
};