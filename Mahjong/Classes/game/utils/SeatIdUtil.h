#ifndef __SEAT_ID_UTIL_H__
#define __SEAT_ID_UTIL_H__
#include "cocos2d.h"
USING_NS_CC;

class SeatIdUtil{
public:
	static int getClientSeatId(int heroId, int seatId);
};

enum ClientSeatId
{
	hero = 1,
	right,
	opposite,
	left
};

#endif