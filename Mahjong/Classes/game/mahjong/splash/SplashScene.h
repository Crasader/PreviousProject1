#ifndef __SPLSH_SCENE_H__
#define __SPLSH_SCENE_H__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "server/NetworkManage.h"
#include "server/CommandManage.h"
USING_NS_CC;
USING_NS_CC_EXT;

class SplashScene : public cocos2d::Layer,public EditBoxDelegate
{
public:
	EditBox* _editName;
	EditBox* _editPwd;
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void onEnter() override;
	virtual void onExit() override;

	void loginByPass();
	void loginByVisitor();
    void setChangeNickName(std::string name,std::string pwd);

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);

	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);

	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);

	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);

	CREATE_FUNC(SplashScene);

private:
		
	EventListenerCustom* loginRespListener;
	EventListenerCustom* roomRespListener;
	EventListenerCustom* reConnectAgain;
    EventListenerCustom* registerRespListener;
    EventListenerCustom* dropListListener;
    EventListenerCustom* heroFirstPoke;
	Sprite* username_text;
	Sprite* password_text;
	void addTocuhListener();
	void drawLonginScene();
	void addCustomEventListener();
	void showUserRegister();
	void findbackPwd();
	void showLoading();
	void removeLoading();
};
#endif