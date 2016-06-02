#include "Rules.h"
#include "Card.h"
#include "MahjongDatas.h"
#include "Room.h"

Rules* Rules::instance = nullptr;

Rules::Rules()
{
	CCLOG("Rules : init");
	init();
}

bool Rules::init()
{
	set_pengPlayer(PLAYER_NULL);
	set_gangPlayer(PLAYER_NULL);
	set_zhuangPlayer(PLAYER_0);
	set_isGameOver(false);
	set_isDianPao(false);
	set_isQiangGang(false);
	return true;
}

//------------------------------------------- 总判断一 --------------------------------------------

// 在一个玩家摸牌之后的判断		1，自己是否可以胡， 2，自己是否可以杠， 3，是否流局
PICK_RESULT Rules::testAfterOnePick(GameFlow & gameFlow)
{
	auto result = testAfterPlayerPick(*(gameFlow.players[gameFlow.currentPlayer]->drawer));
	return result;
}
PICK_RESULT Rules::testAfterPlayerPick(MahjongDrawer & drawer)
{
	if (4 == MahjongDatas::getInstance()->getCardNum())
	{
		return PICK_LIUJU;
	}
	if (2 == drawer.cardInHand.size())
	{
		return drawer[0] == drawer[1] ? PICK_ZIMO : PICK_NEXT;
	}
	else
	{
		if (testCanAnGang(drawer))		// 如果可以暗杠，则肯定是不能胡的。
		{
			return PICK_ANGANG;
		}
		else
		{
			return testCanHu5(drawer) ? PICK_ZIMO : PICK_NEXT;
		}   
	}
}
bool Rules::testCanAnGang(MahjongDrawer & drawer)
{
	int t = drawer[2];
	int diff = 0;
	for (int i = 0; i < 5; i++)
	{
		if (drawer[i] != t)
		{
			if ((++diff) == 2) return false;
		}
	}
	return true;
}
bool Rules::testCanHu5(MahjongDrawer & drawer)
{
	if (drawer[0] == drawer[1])
	{
		if(drawer[3] == drawer[4] && (drawer[1] == drawer[2] || drawer[2] == drawer[3]))		
		{
			return true;	// aaabb || aabbb
		}
		else
		{
			return isThreeBehind(drawer[2], drawer[3], drawer[4]);	// aa bcd
		}
	}
	else
	{
		if (drawer[3] == drawer[4])
		{
			return isThreeBehind(drawer[0], drawer[1], drawer[2]);	// bcd aa
		}
		else
		{
			return  false;
		}
	}
}

//------------------------------------------- 总判断二 --------------------------------------------

// 在一个玩家打牌之后的判断		1，其他所有人是否可以胡，其他某个人是否可以碰
PLAY_RESULT Rules::testAfterOnePlayed(GameFlow & gameFlow)
{
	// 此处有ｂｕｇ，在同时有人碰和胡的时候，会直接碰，而屏蔽胡。
	//CCLOG("Rules : testAfterOnePlayed");

	PLAYER playerIndex = gameFlow.currentPlayer;
	PLAY_RESULT result;
	for (int i = 0; i < 3; i++)
	{
		playerPlusPlus(playerIndex);
		result = testAfterPlayerPlayed(*(gameFlow.players[playerIndex]->drawer));
		switch (result)
		{
		case PLAY_PENG:
			set_pengPlayer(playerIndex);
			//return PLAY_PENG;
			break;
		case PLAY_GANG:
			set_gangPlayer(playerIndex);
			//return PLAY_GANG;
			break;
		case PLAY_DIANPAO:
			gameFlow.players[playerIndex]->set_canHu(true);
			canHuNum++; 
			break;
		case PLAY_NEXT:
			continue;
			break;
		default:
			break;
		}
	}
	if (0 < canHuNum)
	{
		set_isDianPao(true);
		return PLAY_DIANPAO;
	}
	else
	{
		if (PLAYER_NULL != get_pengPlayer())
		{
			return PLAY_PENG;
		}
		if (PLAYER_NULL != get_gangPlayer())
		{
			return PLAY_GANG;
		}
	}
	return PLAY_NEXT;
}

bool Rules::testAfterPlayerGang(MahjongDrawer & drawer)
{
	int playedCard = currentCard->get_type();

	if (1 == drawer.cardInHand.size())
	{
		if (testCanHu1(drawer, playedCard))
		{
			return true;
		}
	}
	else
	{
		if (testCanHu4(drawer, playedCard))
		{
			return true;
		}
	}
	return false;
}

bool Rules::testAfterOneGang(GameFlow & gameFlow)
{

	PLAYER playerIndex = gameFlow.currentPlayer;
	bool result;
	for (int i = 0; i < 3; i++)
	{
		playerPlusPlus(playerIndex);
		result = testAfterPlayerGang(*(gameFlow.players[playerIndex]->drawer));
		if (result)
		{
			gameFlow.players[playerIndex]->set_canHu(true);
			canHuNum++;
		}
	}
	if (0 < canHuNum)
	{
		bool isQiangGang = true;
		return true;
	}
	return false;
}
PLAY_RESULT Rules::testAfterPlayerPlayed(MahjongDrawer & drawer)
{
	int playedCard = currentCard->get_type();

	if (1 == drawer.cardInHand.size())
	{
		if (testCanHu1(drawer, playedCard))
		{
			return PLAY_DIANPAO;
		}
		if (testCanGang1(drawer, playedCard))
		{
			return PLAY_GANG;
		}
	}
	else
	{
		if (testCanGang4(drawer, playedCard))
		{
			return PLAY_GANG;
		}
		if (testCanHu4(drawer, playedCard))
		{
			return PLAY_DIANPAO;
		}
		if (testCanPeng4(drawer, playedCard))
		{
			return PLAY_PENG;
		}
	}
	return PLAY_NEXT;
}
bool Rules::testCanHu1(MahjongDrawer & drawer, const int playedCard)
{
	if (1 != drawer.cardInHand.size() || playedCard != drawer[0])
	{ 
		return false; 
	}
	return true;
}
bool Rules::testCanGang1(MahjongDrawer & drawer, int playedCard)
{
	if (0 != drawer.cardInSide.size())
	{
		if (drawer.cardInSide.at(0)->get_type() == playedCard)
		{
			return true;
		}
	}
	return false;
}
bool Rules::testCanHu4(MahjongDrawer & drawer, const int playedCard)
{
	if (drawer[0] == drawer[1])
	{
		if (drawer[2] == drawer[3])
		{
			if ((playedCard == drawer[0] || playedCard == drawer[3]))
			{
				return true;		// aa bbb, aaa, bb
			}
		}
		else
		{
			if (isThreeBehind(playedCard, drawer[2], drawer[3]))
			{
				return true;		// aa bcd
			}
		}
	}
	else
	{
		if (drawer[2] == drawer[3])
		{
			if (isThreeBehind(playedCard, drawer[0], drawer[1]))
			{
				return true;		// abc, dd
			}
			else if (drawer[1] ==  drawer[2] && drawer[0] == playedCard)
			{
				return true;	// abbb [a]
			}
		}
		else
		{
			if (isThreeBehind(drawer[0], drawer[1], drawer[2]) && drawer[3] == playedCard)
			{
				return true;
			}
			else if (isThreeBehind(drawer[1], drawer[2], drawer[3]) && drawer[0] == playedCard)
			{
				return true;
			}
		}
	}
	return false;
}
bool Rules::testCanGang4(MahjongDrawer & drawer, int playedCard)
{
	if (4 != drawer.cardInHand.size())
	{
		return false;
	}
	int diff = 0;
	for (int i = 0; i < 4; i++)
	{
		if (drawer[i] != playedCard)
		{
			if ((++diff) == 2) return false;
		}
	}
	return true;
}
bool Rules::testCanPeng4(MahjongDrawer & drawer, const int playedCard)
{
	if (4 != drawer.cardInHand.size())
	{
		return false;
	}
	int diff = 0;
	for (int i = 0; i < 4; i++)
	{
		if (drawer[i] != playedCard)
		{
			if ((++diff) == 3) return false;
		}
	}
	return true;
}

//------------------------------------------  胡牌  ---------------------------------------------
void Rules::subCanHuNumToNull(EventCustom* event)
{
	CCLOG("Rules    : subCanHuNumToNull");

	canHuNum--;
	
	if (0 == canHuNum)	// 如果所有人都选择完毕是否胡，Play结束。
	{
		dispatchMahjongEvent(OPERA_DIAMPAO_ENDALL, NULL);
	}
}

void Rules::subCanQiangNumToNull(EventCustom* event)
{
	canHuNum--;
	if (0 == canHuNum)
	{
		dispatchMahjongEvent(OPERA_QIANGGANG_ENDALL, NULL);
	}
}

//------------------------------------------  结算  ---------------------------------------------
void Rules::zhuaNiao(GameFlow & gameFlow)
{
	CCLOG("Rules    : zhuaNiao");
	for (int i = 0; i < 4; i++)
	{
		// 得到鸟数据
		int type = MahjongDatas::getInstance()->popACard();
		int playerIndex = (std::abs(type) - 1) % 4;
		int cardIndex = gameFlow.players[playerIndex]->addNiaoNum();
		
		// 得到鸟图案
		Card* cardNiao = Card::createTableCard(PLAYER_0, type);
		cardNiao->setScale(0.7f);
		cardNiao->setLocalZOrder(9);
		// 鸟画到屏幕
		cardNiao->setPosition(400.0f, 272.0f);
		string str = String::createWithFormat("niao%d", i)->_string;
		gameFlow.addChild(cardNiao, 9, str);
		cardNiao->setVisible(false);

		auto node = Node::create();
		gameFlow.addChild(node);
		Vec2 pos = gameFlow.players[playerIndex]->getChildByName("Head")->getPosition();
		pos.x = pos.x - 50 + cardIndex * 30.0f * 0.7f;

		node->scheduleOnce([i, pos, &gameFlow](float dt){
			// 鸟飞向玩家头像的动画
			string strNiao = String::createWithFormat("niao%d", i)->_string;
			((Card*)gameFlow.getChildByName(strNiao))->cardFadeIn((i+1) * 1.0f, 1.0f, pos);
		}, 3.0f, str);
	}
}

void Rules::accountFanshu(GameFlow & gameFlow)
{
	CCLOG("Rules    : accountFanshu");
	/*
		分数：便利四个玩家，分数 = 番数 * 底分，
		*/
	vector<Player*> playersWin;
	vector<Player*> playersLose;
	maxNiaoNum = 0;
	for (Player* player : gameFlow.players)
	{
		if (RESULT::HU == player->get_Result() || RESULT::ZIMO == player->get_Result())
		{
			player->set_QingYiSe(testSameType(*(player->drawer)));
			playersWin.push_back(player);
			continue;
		}

		if (RESULT::LOSE == player->get_Result() || RESULT::DIANPAO == player->get_Result())
		{
			playersLose.push_back(player);
			continue;
		}
	}
	if (isDianPao)
	{
		accountDianPao(playersWin, playersLose);
	}
	else if (isQiangGang)
	{
		accountQiangGang(playersWin, playersLose);
	}
	else
	{
		accountZiMo(playersWin, playersLose);
	}
	// -------------------------------  计算分数  ----------------------------
	CCLOG("----- Score -----");
	int index = 0;
	int roomScore = getRoomScore();
	for (Player* player : gameFlow.players)
	{
		CCLOG("Player [%d] fan : %d", player->drawer->get_dir(), player->get_FanShu());
		int times = Room::getInstance()->getRoomTimes();
		player->set_Score(player->get_FanShu() * roomScore * times);
		Room::getInstance()->updateCoins(index++, player->get_Score());
	}

}
void Rules::accountZiMo(vector<Player*> & playersWin, vector<Player*> & playersLose)
{
	/*点炮：
	牌型：自摸的人，根据自己的胡牌牌型，计算番数减给输者 == = 输者番数为负
	摸鸟：摸到输者，输者【加2】 | 摸到自摸者，所有输者【加2】
	摸鸟结束所有人番数之和加给自摸者 == = 最终赢番正，输番负，中立0
	*/
	for (Player* playerWin : playersWin)
	{
		set_zhuangPlayer(playerWin->drawer->get_dir());
		CCLOG("----- Win[%d] -----", playerWin->drawer->get_dir());
		int fanshu = 0;
		CCLOG("%d : start", fanshu);

		if (playerWin->get_DaDiaoChe())		{ fanshu += 2; }
		CCLOG("%d : dadiaoche", fanshu);

		if (playerWin->get_PengPengHu())		{ fanshu += 2; }
		CCLOG("%d : peng", fanshu);

		if (playerWin->get_QingYiSe())			{ fanshu += 2; }
		CCLOG("%d : qingyise", fanshu);

		if (playerWin->get_GangKai())			{ fanshu += (0 == fanshu) ? 2 : fanshu; }
		CCLOG("%d : gang", fanshu);

		for (Player* playerLose : playersLose)
		{
			playerLose->set_FanShu(-fanshu);
		}
	}

	// 摸鸟
	CCLOG("----- zhuaNiao -----");
	for (Player* playerLose : playersLose)
	{
		auto m = playerLose->get_FanShu();
		auto n = -2 * playerLose->get_NiaoNum();
		playerLose->set_FanShu(n + m);
	}
	for (Player* playerWin : playersWin)
	{
		auto x = -2 * playerWin->get_NiaoNum();
		for (Player* playerLose : playersLose)
		{
			auto s = playerLose->get_FanShu();
			playerLose->set_FanShu(s + x);
		}
	}
	// -----------------------------------------
	int fan = 0;
	for (Player* playerLose : playersLose)
	{
		fan += playerLose->get_FanShu();
	}
	for (Player* playerWin : playersWin)
	{
		playerWin->set_FanShu(-fan);
	}

}
void Rules::accountDianPao(vector<Player*> & playersWin, vector<Player*> & playersLose)
{
	/*点炮：
	牌型：每个选择了胡牌的人，根据自己的胡牌牌型，计算番数加给自己 == = 赢者番数为正
	摸鸟：摸到输者，所有赢者【番数加2】 | 摸到赢者，赢着【自己加2】 | 摸到中立，不变
	摸鸟结束所有人番数之和减给输者 == = 最终赢番正，输番负，中立0
	*/
	// 计算牌型
	for (Player* playerWin : playersWin)
	{
		if (2 == playerWin->drawer->cardInHand.size())
		{
			playerWin->set_DaDiaoChe(true);
		}
		else
		{
			if ((*(playerWin->drawer))[0] == (*(playerWin->drawer))[1] && (*(playerWin->drawer))[4] == (*(playerWin->drawer))[3])
			{
				playerWin->set_PengPengHu(true);
			}
		}

		CCLOG("----- Win[%d] -----", playerWin->drawer->get_dir());
		int fanshu = 1;
		CCLOG("%d : start", fanshu);

		if (playerWin->get_DaDiaoChe())		{ fanshu += 2; }
		CCLOG("%d : dadiaoche", fanshu);

		if (playerWin->get_PengPengHu())		{ fanshu += 2; }
		CCLOG("%d : peng", fanshu);

		if (playerWin->get_QingYiSe())			{ fanshu += 2; }
		CCLOG("%d : qingyise", fanshu);

		if (fanshu != 1){ fanshu -= 1; }

		if (playerWin->get_GangKai())			{ fanshu *= 2; }
		CCLOG("%d : gang", fanshu);

		playerWin->set_FanShu(fanshu);
	}

	// 计算摸鸟
	CCLOG("----- zhuaNiao -----");
	for (Player* playerWin : playersWin)
	{
		playerWin->set_FanShu(2 * playerWin->get_NiaoNum() + playerWin->get_FanShu());
	}
	for (Player* playerLose : playersLose)
	{
		for (Player* playerWin : playersWin)
		{
			playerWin->set_FanShu(2 * playerLose->get_NiaoNum() + playerWin->get_FanShu());
		}
	}
	// -----------------------------------------
	int fan = 0;
	for (Player* playerWin : playersWin)
	{
		fan += playerWin->get_FanShu();
	}
	for (Player* playerLose : playersLose)
	{
		playerLose->set_FanShu(-fan);
		set_zhuangPlayer(playerLose->drawer->get_dir());
	}
}
void Rules::accountQiangGang(vector<Player*> & playersWin, vector<Player*> & playersLose)
{
	/*自摸:
	牌型：根据自己的胡牌牌型，计算出番数减去给其他所有人
	摸鸟：摸到自己，其他人【番数加倍】 | 摸到他人，他人【番数加倍】 |
	摸鸟结束所有番数之和绝对值加给自己【赢】 == = 最终自己【赢】为正，输番负，中立0
	*/
	// 计算牌型
	for (Player* playerWin : playersWin)
	{
		CCLOG("----- Win[%d] -----", playerWin->drawer->get_dir());
		int fanshu = 2;
		CCLOG("%d : start", fanshu);

		if (playerWin->get_PengPengHu())		{ fanshu += 2; }
		CCLOG("%d : peng", fanshu);

		if (playerWin->get_QingYiSe())			{ fanshu += 2; }
		CCLOG("%d : qingyise", fanshu);

		if (playerWin->get_GangKai())			{ fanshu *= 2; }
		CCLOG("%d : gang", fanshu);
		for (Player* playerL : playersLose)
		{
			playerL->set_FanShu(-fanshu);
		}
	}

	// 计算摸鸟
	for (Player* playerWin : playersWin)
	{
		for (Player* playerLose : playersLose)
		{
			playerLose->set_FanShu(2 * playerWin->get_NiaoNum() + playerLose->get_FanShu());
		}
	}
	for (Player* playerLose : playersLose)
	{
		playerLose->set_FanShu(2 * playerLose->get_NiaoNum() + playerLose->get_FanShu());
	}

	// ---------------------------------------------
	int fan = 0;
	for (Player* playerLose : playersLose)
	{
		fan += playerLose->get_FanShu();
	}
	for (Player* playerWin : playersWin)
	{
		playerWin->set_FanShu(-fan);
	}
}
int Rules::getRoomScore()
{
    return Room::getInstance()->updateRoomScore();
}

// 测试是否清一色，true表示清一色，false表示没有清一色
bool Rules::testSameType(MahjongDrawer & drawer)
{
	CCLOG("Rules    : testSameType");
	int start = 0;
	int end = drawer.cardInHand.size() - 1;
	if (0 > drawer[start] * drawer[end])
	{
		return false;		// 手牌不同
	}
	if (0 != drawer.cardInSide.size())
	{
		if (0 > drawer[start] * drawer.cardInSide.at(0)->get_type())
		{
			return false;	// 手牌和碰杠牌不同
		}
	}
	return true;
}
// 从剩下的牌中摸四张鸟
// 没有引用，游戏开始时象征性扔筛子。。
Sprite* Rules::creatShaiZi()
{
	Size size = Director::getInstance()->getWinSize();
	Sprite *shaizi = Sprite::create();
	shaizi->setPosition(size.width / 2, size.height / 2);
	string strArray[6] =
	{
		"ShaiZi/1.png",
		"ShaiZi/2.png",
		"ShaiZi/3.png",
		"ShaiZi/4.png",
		"ShaiZi/5.png",
		"ShaiZi/6.png"
	};
	Vector<SpriteFrame*> spriteFrameVect;
	for (int i = 0; i < 6; i++)
	{
		SpriteFrame *oneFrame = SpriteFrame::create(strArray[i], Rect(0, 0, 41, 45));
		spriteFrameVect.pushBack(oneFrame);
	}
	Animation *anim = Animation::createWithSpriteFrames(spriteFrameVect, 0.15f);
	Animate *shaiziAnimate = Animate::create(anim);
	Sequence *seq = Sequence::create(Repeat::create(shaiziAnimate->clone(), 3),
		CallFunc::create([=](){
		int rand = random<int>(0, 5);
		shaizi->setSpriteFrame(spriteFrameVect.at(rand));
	}), NULL);
	shaizi->runAction(seq);
	return shaizi;
}

//-----------------------------------------  辅助函数  ---------------------------------------------
bool Rules::isThreeBehind(int a, int b, int c)
{
	if (a > b){ swap(a, b); }
	if (b > c){ swap(b, c); }
	if (a > c){ swap(a, c); }
	return (b - a == 1) && (c - b == 1);
}

bool Rules::isThreeSame(int a, int b, int c)
{
	if (a == b && b == c){ return true; }
	return false;
}
