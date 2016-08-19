#ifndef __TRUSTEESHIP_H__
#define __TRUSTEESHIP_H__
#include "cocos2d.h"
USING_NS_CC;

class Trusteeship :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(Trusteeship);
protected:
	virtual void drawDialog();
	void closeView();
private:
	bool onTouchBegan(Touch *touch, Event  *event);
};
#endif