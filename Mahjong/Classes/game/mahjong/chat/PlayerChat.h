#ifndef __PLAYER_CHAT_H__
#define __PLAYER_CHAT_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

enum PlayerChatType
{
	image,
	text,
	sound
};

class PlayerChat :public Layer{
public :
	virtual bool init();
	void showPlayerChat(PlayerChatType type,int seatId,int infoId);
	CREATE_FUNC(PlayerChat);
private:
	void drawFaceImage(int seatId,int id);
	void drawTextInfo(int seatId,int id);
	void drawSoundInfo(int seatId, int id);
};
#endif