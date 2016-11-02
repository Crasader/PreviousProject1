#ifndef __GUI_LAYER_H__
#define __GUI_LAYER_H__
#include "cocos2d.h"
USING_NS_CC;

class GuiLayer:public Layer{
public:
	virtual bool init();
    void onEnter() override;
    void onExit() override;
	void updateData();
	void hideInvitePlayer(int clientId);
    void showInvitePlayer(int clientId);
    void hideDissovleBtn();
	CC_SYNTHESIZE(bool, showChat,ShowChat);
	CREATE_FUNC(GuiLayer);
private:
	LabelAtlas* kaibaoNum;
	LabelAtlas* haungNum;
	Menu* leftPlayerInvite;
	Menu* rightPlayerInvite;
	Menu* oppositePlayerInvite;
	void initView();
	void soundButtonClick();
	void chatButtonClick();
	void settingButtonClick();
	void quitButtonClick();
	void drawPlayerInvite();
    void showPlayerBill();
	void invitePlayer(Ref* ref);
    void dissovleRoom();
    
};
#endif