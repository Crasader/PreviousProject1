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

	int updateRoomScore();	// �������ǽ�ң����µ׷�
	int addFreeCoins();			// �ĸ���ҽ�Ҳ������������������ӽ��

	int getRoomScore();			// �õ��׷�
	int getRoomTimes();			// �õ����䱶��
	int getCoins(int id);			// �õ�ĳ����ҵ�Ӳ��
	
	void setRoomTimes(int newTimes);	// ���ñ���


	// updateCoins(0, -1000) ����ң������ݣ����٣���������Ӳ��
	void updateCoins(int id, int newCoins);	// ����ĳ����ҵ�Ӳ��

private:
	static Room* instance;
	int roomScore[4];			// �ĸ�����ĵ׷�
	int coins[4];			// 
	ROOM roomID = ROOM_1;// ��ǰ�����
	int times;						// ����
};

#endif