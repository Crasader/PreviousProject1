#ifndef __SEAT_ID_UTIL_H__
#define __SEAT_ID_UTIL_H__
#include "cocos2d.h"
USING_NS_CC;

class SeatIdUtil{
public:
	static int getClientSeatId(int heroId, int seatId);
    static int getServerPreSeatId(int current);//获取上一位玩家的服务端座位号
};

enum ClientSeatId
{
	hero = 1,
	right,
	opposite,
	left
};

#endif
