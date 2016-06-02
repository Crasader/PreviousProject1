#ifndef __USER_REGISTER_H__
#define __USER_REGISTER_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "game/mahjong/dialog/base/BaseDialog.h"

USING_NS_CC;
USING_NS_CC_EXT;

class UserRegister : public BaseDialog, public EditBoxDelegate{
public:
	virtual bool init();
	void onEnter() override;
	void onExit() override;
	CREATE_FUNC(UserRegister);

	//��ʼ����༭
	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	//�����༭
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	//�༭���ı��ı�
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
	//������return��Ļص�����
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
private:
	EditBox* _editName;
	EditBox* _editPwd;
	EditBox* _editPwd2;
	EventListenerCustom* checkAccountListener;
	Sprite* account_hint_info;
	Sprite* password_hint_info;
	Sprite* password_hint_info2;
	Sprite* account_input_info;
	Sprite* password_input_info;
	void drawDialog() override;
	void registerConfirm();
	bool checkAccount(std::string std);
	bool checkPassword(std::string std);
	CC_SYNTHESIZE(bool,allow,Allow);
};
#endif