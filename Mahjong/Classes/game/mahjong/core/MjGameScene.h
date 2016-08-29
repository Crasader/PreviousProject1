#ifndef __MJGAME_SCENE_H__
#define __MJGAME_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;
class MjGameScene:public Scene{
public:
	virtual bool init();
    void onEnter() override;
    void onExit() override;
	CREATE_FUNC(MjGameScene);
private:
    EventListenerCustom* enterFrinedRoomListener;
};
#endif