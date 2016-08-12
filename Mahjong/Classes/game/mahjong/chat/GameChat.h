#ifndef __GAME_CHAT_H__
#define __GAME_CHAT_H__
#include "cocos2d.h"
USING_NS_CC;

class GameChat :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameChat);
private:
	MenuItemToggle* textToggleMenuItem;
	MenuItemToggle*	faceToggleMenuItem;
	Menu* faceMenu;
	void drawDialog();
	void addAllFace();
	void faceToggleCallback(Ref* psend);
	void textToggleCallback(Ref* psend);
	void faceSelected(Ref* ref);
	void isShowFace(bool show);
	bool onTouchBegan(Touch *touch, Event  *event);
};
#endif