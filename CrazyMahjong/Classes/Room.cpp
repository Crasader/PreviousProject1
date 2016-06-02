#include "Room.h"

Room* Room::instance = nullptr;

Room::Room()
{
	roomScore[0] = 200;	// 低分
	roomScore[1] = 400;
	roomScore[2] = 800;
	roomScore[3] = 1000;

	coins[0] = 0;
	coins[1] = 0;
	coins[2] = 0;
	coins[3] = 0;
}
// 根据硬币数，更新房间号
int Room::updateRoomScore()
{
	if (1000 > coins[0])
	{
		// 充值
		coins[0] = 1000;
		roomID = ROOM_1;
	}
	else if (1000 <= coins[0] && 8000 > 8000)
	{
		roomID = ROOM_1;
	}
	else if (8000 <= coins[0] && 16000 >= coins[0])
	{
		roomID = ROOM_2;
	}
	else if (16000 <= coins[0] && 40000 >= coins[0])
	{
		roomID = ROOM_3;
	}
	else if (40000 <= coins[0])
	{
		roomID = ROOM_4;
	}
	return roomScore[roomID];
}

int Room::getRoomScore()
{
	return roomScore[roomID];
}

// 给电脑增加硬币
int Room::addFreeCoins()
{
	for (int index = 1; index < 4; index++)
	{
		if (1000 > coins[index])
		{
			coins[index] += 1000;
		}
	}
	return 0;
}

int Room::getCoins(int id)
{
	return coins[id];
}

void Room::setRoomTimes(int newTimes)
{
	times = newTimes;
}

int Room::getRoomTimes()
{
	return times;
}

void Room::updateCoins(int id, int newCoins)
{
	coins[id] += newCoins;
}