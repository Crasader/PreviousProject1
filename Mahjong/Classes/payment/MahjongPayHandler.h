#ifndef _MENU_SCENE_PAY_HANDLER_H_
#define _MENU_SCENE_PAY_HANDLER_H_
#include "cocos2d.h"

class MahjongPayHandler
{       
public:
	MahjongPayHandler() {};
	~MahjongPayHandler() {};
	void dealEventSuccess(int eventId, int propIds[], int propNums[], int count);
	void dealEventFail(int eventId);
	void dealRewardProp(int propId, int propNum);
	void dealEventClose(int eventId);
	static MahjongPayHandler* getInstance();
private:
	void doPayEvent1(int result);
	void doPayEvent2(int result);
	void doPayEvent3(int result);
};
#endif

