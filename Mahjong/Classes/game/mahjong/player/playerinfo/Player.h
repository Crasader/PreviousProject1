#ifndef __PLAYER_INFO_H__
#define __PLAYER_INFO_H__
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class Player
{
public:
	Player();
	~Player();
	CC_SYNTHESIZE(int, type, Type);
	CC_SYNTHESIZE(int, gold, Gold);
	CC_SYNTHESIZE(int, diamond, Diamond);
	CC_SYNTHESIZE(int, lockDiamond, LockDiamond);
    CC_SYNTHESIZE(int, fangka, Fangka);
	CC_SYNTHESIZE(int, ticket, Ticket);
	CC_SYNTHESIZE(int, seatId, SeatId);
	CC_SYNTHESIZE(int, score, Score);
	CC_SYNTHESIZE(bool, gender, Gender);
	CC_SYNTHESIZE(bool, isReady, IsReady);
	CC_SYNTHESIZE(bool, banker, Banker);
	CC_SYNTHESIZE(string, poxiaoId, PoxiaoId);
	CC_SYNTHESIZE(string, nickName, Nickname);
	CC_SYNTHESIZE(string, pic, Picture);
	CC_SYNTHESIZE(Point, pos, Position);
};
#endif