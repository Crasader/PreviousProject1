#ifndef __PLAY_MENU_H__
#define __PLAY_MENU_H__

#include "cocos2d.h"
USING_NS_CC;

#include "MahjongEvent.h"
#include "Player.h"

class GameFlow;

class MahjongControler;

class PlayMenu : public Node
{
public:
	CREATE_FUNC(PlayMenu);
	void getPlayer(Player* const player);

	void ShowPengButton();
	void ShowAnGangButton();
	void ShowGangButton();
	void ShowPengAndGang();
	void ShowQiangGangButton();

	void ShowZiMoButton();
	void ShowDianPaoButton();

	void getInfo(int newCoins, int newTimes);

private:
	bool init();

	void hide();
	// 发牌回调
	void dealGoodBtnCallBack(Ref* pSender);
	void dealBtnCallBack(Ref* pSender);
	// 碰杠胡的回调
	void pengCallback(Ref* pSender);
	void gangCallback(Ref* pSender);
	void anGangCallback(Ref* pSender);
	void ziMoCallback(Ref* pSender);
	void dianPaoCallback(Ref* pSender);
	void qiangGangCallback(Ref* pSender);
	// 弃的回调
	void qiPengCallback(Ref* pSender);
	void qiGangCallback(Ref* pSender);
	void qiAnGangCallback(Ref* pSender);
	void qiZiMoHuCallback(Ref* pSender);
	void qiDianPaoCallback(Ref* pSender);
	void qiQiangGangCallback(Ref* pSender);

	Player* player;
	MenuItemImage* peng;
	MenuItemImage* gang;
	MenuItemImage* hu;
	MenuItemImage* qi;

	LabelAtlas* label = nullptr;
	LabelAtlas* labelTimes = nullptr;
	Node* roomInfoNode = nullptr;

};

#endif // !__PLAY_MENU_H__
