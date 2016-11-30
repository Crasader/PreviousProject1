#ifndef __GUI_LAYER_H__
#define __GUI_LAYER_H__
#include "cocos2d.h"
USING_NS_CC;

class GuiLayer:public Layer{
public:
	virtual bool init() override;
    void onEnter() override;
    void onExit() override;
	void updateData();
	void hideInvitePlayer(int clientId);
    void showInvitePlayer(int clientId);
    void hideDissovleBtn();
	CC_SYNTHESIZE(bool, showChat,ShowChat);
	CREATE_FUNC(GuiLayer);
private:
	Label* kaibaoNum;
	Label* haungNum;
	Menu* leftPlayerInvite;
	Menu* rightPlayerInvite;
	Menu* oppositePlayerInvite;
	void initView();
    void drawGameInfo();//开宝，荒翻,房号
    void drawGuiButton();//设置,账单,聊天
	void soundButtonClick();
	void chatButtonClick();
	void settingButtonClick();
	void quitButtonClick();
	void drawPlayerInvite();
    void showPlayerBill();
	void invitePlayer(Ref* ref);
    void dissovleRoom();
    void update(float dt) override;
    
};
#endif
