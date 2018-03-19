#ifndef __ORIENTATION_H__
#define __ORIENTATION_H__
#include "cocos2d.h"
USING_NS_CC;

class Orientation :public Node{
public:
	virtual bool init();
	CREATE_FUNC(Orientation);
	void showOrientation(int heroSeatId);
	void showPlayerTurn(int heroSeatId, int setaId);
    void showWhoBank(int heroSeatId,int bankId);
    void resetBank();
private:
	Sprite* left;
	Sprite* right;
	Sprite* opposite;
	Sprite* hero;
	Sprite* light;
	void initView();
	void changeTeture(Sprite* node);
    void recoverTeture(Sprite* node);
    void updateTime(float dt);
};
#endif 
