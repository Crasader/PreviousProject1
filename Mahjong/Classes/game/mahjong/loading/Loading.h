#ifndef __ENTER_ROOM_LOAD_H__
#define __ENTER_ROOM_LOAD_H__
#include "cocos2d.h"
USING_NS_CC;

class Loading : public Layer{
public:
    static Loading* create();
    static Loading* create(bool touchAble);
    static Loading* create(Point pos,bool touchAble);
    virtual bool init(Point pos,bool touchAble);
private:
    void update(float dt);
    int connectOutTime = 10;
	void craeteAnimate(Point pos);
	bool onTouchBegan(Touch *touch, Event  *event);
}; 
#endif