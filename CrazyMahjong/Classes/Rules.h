// �齫������

#ifndef __RULES_H__
#define __RULES_H__

#include "Player.h"
#include "GameFlow.h"
#include "MahjongEvent.h"

class Rules
{
public:
	Rules();

	static Rules* getInstance()
	{
		if (nullptr == instance)
		{
			instance = new Rules();
		}
		return instance;
	}

	bool init();

	void accountFanshu(GameFlow & gameFlow);
	void accountZiMo(vector<Player*> & playersWin, vector<Player*> & playersLose);
	void accountDianPao(vector<Player*> & playersWin, vector<Player*> & playersLose);
	void accountQiangGang(vector<Player*> & playersWin, vector<Player*> & playersLose);
	bool isWinner(PLAYER & card);


	bool canKaiGang(MahjongDrawer* drawer);
	
	// ץ��
	void zhuaNiao(GameFlow & gameFlow);

	// ��һ���������֮����ж�		1,�Լ��Ƿ���Ժ�  2���Լ��Ƿ���Ը�
	PICK_RESULT testAfterOnePick(GameFlow & gameFlow);

	// ��һ����Ҵ���֮����ж�		1�������������Ƿ���Ժ�������ĳ�����Ƿ������
	PLAY_RESULT testAfterOnePlayed(GameFlow & gameFlow);

	bool testAfterOneGang(GameFlow & gameFlow);

	void subCanHuNumToNull(EventCustom* event);
	void subCanQiangNumToNull(EventCustom* event);

	CC_SYNTHESIZE(PLAYER, zhuangPlayer, _zhuangPlayer);
	CC_SYNTHESIZE(Card*, currentCard, _currentCard);
	CC_SYNTHESIZE(PLAYER, pengPlayer, _pengPlayer);
	CC_SYNTHESIZE(PLAYER, gangPlayer, _gangPlayer);
	CC_SYNTHESIZE(bool, isGameOver, _isGameOver);
	CC_SYNTHESIZE(bool, isDianPao, _isDianPao);
	CC_SYNTHESIZE(bool, isQiangGang, _isQiangGang);
	CC_SYNTHESIZE(int, maxNiaoNum, _maxNiaoNum);
private:
	static Rules* instance;

	int canHuNum = 0;
	
	// �����Ƿ���һɫ
	bool testSameType(MahjongDrawer & drawer);
	
	PICK_RESULT testAfterPlayerPick(MahjongDrawer & drawer);
	bool testCanAnGang(MahjongDrawer & drawer);
	bool testCanHu5(MahjongDrawer & drawer);

	PLAY_RESULT testAfterPlayerPlayed(MahjongDrawer & drawer);
	bool testCanHu1(MahjongDrawer & drawer, const int playedCard);
	bool testCanHu4(MahjongDrawer & drawer, const int playedCard);
	bool testCanGang1(MahjongDrawer & drawer, const int playedCard);
	bool testCanGang4(MahjongDrawer & drawer, const int playedCard);
	bool testCanPeng4(MahjongDrawer & drawer, const int playedCard);

	bool testAfterPlayerGang(MahjongDrawer & drawer);

	bool isThreeBehind(int a, int b, int c);
	bool isThreeSame(int a, int b, int c);

	int getRoomScore();
	//
	Sprite *creatShaiZi();
};

#endif // !__RULES_H__
