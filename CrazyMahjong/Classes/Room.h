#ifndef __ROOM_H__
#define __ROOM_H__

enum ROOM
{
	ROOM_1 = 0,
	ROOM_2 = 1,
	ROOM_3 = 2,
	ROOM_4 = 3,
};

class Room
{

public:
	Room();
	static Room* getInstance()
	{
		if (nullptr == instance)
		{
			instance = new Room;
		}
		return instance;
	}

	int updateRoomScore();	// 根据主角金币，更新底分
	int addFreeCoins();			// 四个玩家金币不够１０００，　增加金币

	int getRoomScore();			// 得到底分
	int getRoomTimes();			// 得到房间倍数
	int getCoins(int id);			// 得到某个玩家的硬币
	
	void setRoomTimes(int newTimes);	// 设置倍数


	// updateCoins(0, -1000) 给玩家１的数据，减少１０００个硬币
	void updateCoins(int id, int newCoins);	// 更新某个玩家的硬币

private:
	static Room* instance;
	int roomScore[4];			// 四个房间的底分
	int coins[4];			// 
	ROOM roomID = ROOM_1;// 当前房间号
	int times;						// 倍数
};

#endif