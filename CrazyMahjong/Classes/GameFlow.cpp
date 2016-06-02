
#include "GameFlow.h"
#include "Rules.h"
#include "UIPos.h"
#include "MahjongDatas.h"
#include "Room.h"
#include "MahjongAnim.h"
#include "SystemUI.h"
//---------------------------------------   游戏流程    -------------------------------------------

//------------------------------------------ 初始化 ----------------------------------------------
bool GameFlow::init()
{
	CCLOG("GameFlow : init");

	if (!Node::init())
	{
		return false;
	}
	isGameOver = false;

	//this->addChild( AddCoinPanel::create());

	Room::getInstance();
	
	pRules = Rules::getInstance();
	pRules->init();

	MahjongDatas::getInstance()->initData();
	
	initPlayers();

	// 返回，设置，更多游戏，充值金币
	SystemUI* systemUI = SystemUI::create();
	this->addChild(systemUI);

	// 结算面板
	panel = AccountPanel::create();
	panel->setLocalZOrder(10);
	this->addChild(panel);

	// 动画
	MahjongAnim::updateInstance();
	auto anim = MahjongAnim::getInstance();
	anim->setLocalZOrder(11);
	if (nullptr != anim->getParent())
	{
		anim->removeFromParent();
	}
	CCLOG("+++++++++++++++++ debug addAnim To1 GameFlow");
	this->addChild(anim);
	CCLOG("+++++++++++++++++ debug addAnim To2 GameFlow");

	MahjongAnim::getInstance()->playSound(SOUND::BGM);

	return true;
}

void GameFlow::onEnter() 
{
	CCLOG("GameFlow : onEnter");
	Node::onEnter();
	addGameFlowEvent();
}

void GameFlow::onExit()
{
	Node::onExit();	

	//_eventDispatcher->resumeEventListenersForTarget(this, true);
	removeMahjongListener(DEALCARDS);

	removeMahjongListener(OPERA_PICK_END);
	removeMahjongListener(OPERA_PLAY_END);
	removeMahjongListener(OPERA_PENGGANG_END);
	removeMahjongListener(QI_RETURN_BEFORE);
	removeMahjongListener(DELETE_TABLE_BEFORE);

	removeMahjongListener(OPERA_ZIMO_END);
	removeMahjongListener(OPERA_DIANPAO_END);
	removeMahjongListener(	OPERA_DIAMPAO_ENDALL);
	removeMahjongListener(OPERA_QIANGGANG_END);
	removeMahjongListener(OPERA_QIANGGANG_ENDALL);
	removeMahjongListener(GAME_OVER);

	int coins = Room::getInstance()->getCoins(0);
	UserDefault::getInstance()->setIntegerForKey("coins", coins);
	UserDefault::getInstance()->flush();
}

void GameFlow::initPlayers()
{
	CCLOG("");
	CCLOG("GameFlow : init Players");
	//Vec2(*cardHandPos)[5] = getHandCardPos();
	auto room = Room::getInstance();

	// 如果主角是重新进游戏
	if (0 == room->getCoins(0))
	{
		int mainCoin = UserDefault::getInstance()->getIntegerForKey("coins", 1000);
		room->updateCoins(0, mainCoin);
		for (int i = 1; i < 4; i++)
		{
			int newCoins = random<int>(1000, 5000);
			newCoins = newCoins / 10 * 10;
			room->updateCoins(i, newCoins);
		}
	}
	
	room->addFreeCoins();

	for (int i = 0; i < 4; i++)
	{
		players[i] = NULL;
		players[i] = Player::createPlayer((PLAYER)i);
		this->addChild(players[i]);
		//players[i]->drawer->cardPos = cardHandPos[i];
		//players[i]->drawer->cardPos = getHandCardPs(i);	//两种方法
	}

	players[PLAYER_0]->set_isPlayer(true);
	Player::playMenu = initMenu();
	Player::playMenu->getPlayer(players[PLAYER_0]);
}
PlayMenu* GameFlow::initMenu()
{	
	CCLOG("");
	CCLOG("GameFlow : initMenu");
	PlayMenu* playMenu = PlayMenu::create();
	this->addChild(playMenu);
	return playMenu;
}
void GameFlow::addGameFlowEvent()
{
	CCLOG("GameFlow : addGameFlowEvent");
	addMahjongListener(FLOW_NAME::DEALCARDS, 
		CC_CALLBACK_1(GameFlow::onDealCardsBegin, this));

	addMahjongListener(FLOW_NAME::OPERA_PLAY_END, 
		CC_CALLBACK_1(GameFlow::onOperaPlayEnd, this) );
	addMahjongListener(FLOW_NAME::OPERA_PENGGANG_END,
		CC_CALLBACK_1(GameFlow::onOperaPengGangEnd, this));
	addMahjongListener(FLOW_NAME::QI_RETURN_BEFORE,
		CC_CALLBACK_1(GameFlow::returnBefore, this)); 
	addMahjongListener(FLOW_NAME::DELETE_TABLE_BEFORE,
		CC_CALLBACK_1(GameFlow::deleteTableBefore, this));

	

	addMahjongListener(FLOW_NAME::OPERA_ZIMO_END,
		CC_CALLBACK_1(GameFlow::onOperaZiMoEnd, this));

	addMahjongListener(FLOW_NAME::OPERA_DIANPAO_END,
		CC_CALLBACK_1(Rules::subCanHuNumToNull, pRules));
	addMahjongListener(FLOW_NAME::OPERA_DIAMPAO_ENDALL,
		CC_CALLBACK_1(GameFlow::onOperaDianPaoEnd, this));

	addMahjongListener(FLOW_NAME::OPERA_QIANGGANG_END,
		CC_CALLBACK_1(Rules::subCanQiangNumToNull, pRules));
	addMahjongListener(FLOW_NAME::OPERA_QIANGGANG_ENDALL
		,CC_CALLBACK_1(GameFlow::onOperaQiangGangEnd, this));

	addMahjongListener(FLOW_NAME::GAME_OVER, 
		CC_CALLBACK_1(GameFlow::onGameOver, this));
}

//-------------------------------------------- 发牌 ----------------------------------------------
void GameFlow::onDealCardsBegin(EventCustom* event)
{
	auto room = Room::getInstance();
	Player::playMenu->getInfo(room->updateRoomScore(), room->getRoomTimes());
	CCLOG("GameFlow : onDealCardsBegin");
	CCLOG("");
	currentPlayer = pRules->get_zhuangPlayer();
	// 每隔0.2s发一张牌，发17张
	MahjongAnim::getInstance()->playDealShaiZi();
	schedule(schedule_selector(GameFlow::dealACard), 0.2f, 16, 1.5f);
	schedule(schedule_selector(GameFlow::startGame), 7.0f, 0, 7.0f);
}

void GameFlow::dealACard(float dt)
{
	CCLOG("GameFlow : dealACard");
	players[currentPlayer]->operaPick();
	playerPlusPlus(currentPlayer);
}

void GameFlow::startGame(float dt)
{
	CCLOG("");
	CCLOG("GameFlow : startGame");
	addMahjongListener(OPERA_PICK_END, CC_CALLBACK_1(GameFlow::onOperaPickEnd, this));
	currentPlayer = pRules->get_zhuangPlayer();
	players[currentPlayer]->set_isZhuang(true);
	for (int i = 0; i < 4; i++)
	{
		players[i]->initLogo();
	}
	sortCardForAll();

	CCLOG("");
	// 发牌之后，游戏开始，进行庄家的摸牌判断	
	dispatchMahjongEvent(OPERA_PICK_END, NULL);
}
//------------------------------------------- 摸牌后 ----------------------------------------------
void GameFlow::onOperaPickEnd(EventCustom* event)
{
	CCLOG("---------------------------------------------------------------");
	CCLOG("-------------------GameFlow : Player[%d]PickEnd-------------------", currentPlayer);
	CCLOG("---------------------------------------------------------------");
	auto result = pRules->testAfterOnePick(*this);

	/*if (currentPlayer == 3)
	{
		result = PICK_PENGGANG;
	}*/

	switch (result)
	{
	case PICK_ZIMO:
		players[currentPlayer]->operaZiMo();
		break;
	case PICK_ANGANG:
		players[currentPlayer]->operaAnGang();
		break;
	case PICK_PENGGANG:
		players[currentPlayer]->operaPengGang();
		break;
	case PICK_NEXT:
		players[currentPlayer]->operaPlay();
		break;
	case PICK_LIUJU:
		showAccount(true);
		break;
	default:
		break;
	}
}

void GameFlow::onOperaZiMoEnd(EventCustom* event)
{
	if (ZIMO == players[currentPlayer]->get_Result())
	{
		PLAYER losePlayer = currentPlayer;
		for (int i = 0; i < 3; i++)
		{
			playerPlusPlus(losePlayer);
			players[losePlayer]->set_Result(LOSE);
		}
		dispatchMahjongEvent(GAME_OVER, (void*)0);
	}
	else
	{
		players[currentPlayer]->operaPlay();
	}
}
//------------------------------------------- 碰杠后 ---------------------------------------------------
void GameFlow::onOperaPengGangEnd(EventCustom* event)
{
	CCLOG("------------------GameFlow : Player[%d]PengGangEnd------------------", currentPlayer);
	if (pRules->testAfterOneGang(*this))
	{
		// 有人抢杠
		OperaWhenCanQiangGang();
	}
	else
	{
		// 没人抢杠
		players[currentPlayer]->goOnOperaPick();
	}
}

void GameFlow::OperaWhenCanQiangGang()
{
	beforePlayer = currentPlayer;

	CCLOG("GameFlow : OperaWhenCanQiangGang");

	for (int i = 0; i < 4; i++)
	{
		if (players[i]->get_canHu())
		{
			currentPlayer = (PLAYER)i;
			CCLOG("Player %d : canQiangGang", i);
			players[currentPlayer]->operaQiangGang();
		}
	}
}

void GameFlow::onOperaQiangGangEnd(EventCustom* event)
{
	CCLOG("GameFlow : onAllQiangGangOperaEnd");
	for (Player* player : players)
	{
		if (HU == player->get_Result())
		{
			pRules->set_isQiangGang(true);
			players[beforePlayer]->set_Result(DIANPAO);
			Card* card = Rules::getInstance()->get_currentCard();
			player->drawer->cardInHand.push_back(card);
			player->drawer->sortData();
			CCLOG("Win : %d ----------- Lose : %d", player->drawer->get_dir(), beforePlayer);
			set_isGameOver(true);
			break;
		}
	}
	if (isGameOver)
	{
		dispatchMahjongEvent(GAME_OVER, (void*)2);
	}
	else
	{
		pRules->subCanHuNum();
		players[currentPlayer]->operaPick();
	}
}
//------------------------------------------- 打牌后 ---------------------------------------------------
void GameFlow::onOperaPlayEnd(EventCustom* event)
{
	CCLOG("---------------------------------------------------------------");
	CCLOG("------------------GameFlow : Player[%d]PlayEnd------------------", currentPlayer);
	CCLOG("---------------------------------------------------------------");

	players[currentPlayer]->drawer->sortCard();

	PLAY_RESULT result = pRules->testAfterOnePlayed(*this);

	//if (currentPlayer >= 0)
	//{
	//	result = PLAY_PENG;
	//	pRules->set_pengPlayer(playerPlusPlus(currentPlayer));
	//}

	switch (result)
	{
	case PLAY_DIANPAO:
		OperaWhenCanDianPaoHu();
		break;

	case PLAY_PENG:
		CCLOG("Result : Peng");
		beforePlayer = currentPlayer;
		currentPlayer = pRules->get_pengPlayer();
		pRules->set_pengPlayer(PLAYER::PLAYER_NULL);
		players[currentPlayer]->operaPeng();
		break;

	case PLAY_GANG:
		beforePlayer = currentPlayer;
		currentPlayer = pRules->get_gangPlayer();
		pRules->set_gangPlayer(PLAYER_NULL);

		if (0 < players[currentPlayer]->drawer->cardInSide.size())
		{
			players[currentPlayer]->operaPengGang();
		}
		else
		{
			players[currentPlayer]->operaGang();
		}
		break;

	case PLAY_NEXT:
		turnToNext();
		break;

	default:
		CCLOG("======== Rules : TestAfterOnePlayed : Wrong");
		break;
	}
}
void GameFlow::deleteTableBefore(EventCustom* event)
{
	players[beforePlayer]->drawer->remove1CardInTable();
}



void GameFlow::OperaWhenCanDianPaoHu()
{
	beforePlayer = currentPlayer;

	CCLOG("GameFlow : OperaWhenCanDianPaoHu");

	for (int i = 0; i < 4; i++)
	{
		if (players[i]->get_canHu())
		{
			currentPlayer = (PLAYER)i;
			CCLOG("Player %d : canDianPao", i);
			players[i]->operaDianPao();
		}
	}
}

void GameFlow::onOperaDianPaoEnd(EventCustom* event)
{
	CCLOG("GameFlow : onAllHuOperaEnd");
	for (Player* player : players)
	{
		if (HU == player->get_Result())
		{
			players[beforePlayer]->set_Result(DIANPAO);
			Card* card = Rules::getInstance()->get_currentCard();
			player->drawer->cardInHand.push_back(card);
			player->drawer->sortData();
			CCLOG("Win : %d ----------- Lose : %d", player->drawer->get_dir(), beforePlayer);
			set_isGameOver(true);
		}
	}
	if (isGameOver)
	{
		dispatchMahjongEvent(GAME_OVER, (void*)1);
	}
	else
	{
		dispatchMahjongEvent(QI_RETURN_BEFORE, NULL);
	}
}

void GameFlow::returnBefore(EventCustom* event)
{
	CCLOG("");
	CCLOG("GameFlow : onNext");
	currentPlayer = beforePlayer;

	if (PLAYER_NULL != pRules->get_pengPlayer())
	{
		CCLOG("return DianPao and : Peng");
		beforePlayer = currentPlayer;
		currentPlayer = pRules->get_pengPlayer();
		pRules->set_pengPlayer(PLAYER::PLAYER_NULL);
		players[currentPlayer]->operaPeng();
		return;
	}

	if (PLAYER_NULL != pRules->get_gangPlayer())
	{
		beforePlayer = currentPlayer;
		currentPlayer = pRules->get_gangPlayer();
		pRules->set_gangPlayer(PLAYER_NULL);

		if (0 < players[currentPlayer]->drawer->cardInSide.size())
		{
			players[currentPlayer]->operaPengGang();
		}
		else
		{
			players[currentPlayer]->operaGang();
		}
		return;
	}

	turnToNext();
}
void GameFlow::turnToNext()
{
	CCLOG("GameFlow : turnToNext");
	currentPlayer = (PLAYER)((currentPlayer+1)%4);
	beforePlayer = currentPlayer;
	auto card = players[currentPlayer]->operaPick();
	card->runAction(MoveBy::create(0.1f, MahjongDrawer::cardPickDis[currentPlayer]));
	card->setLocalZOrder( 1 == players[currentPlayer]->drawer->get_dir() ? -10 : 10 );
}
//------------------------------------------ 胜负已分 -------------------------------------------------------------
void GameFlow::onGameOver(EventCustom* event)
{
	CCLOG("---------------------------------------------------------------");
	CCLOG("------------------GameFlow : onGameOver---------------");
	CCLOG("---------------------------------------------------------------");

	// 这里是个什么原理？？？
	pRules->zhuaNiao(*this);
	pRules->accountFanshu(*this);

	auto result = (int)event->getUserData();
	if (0 == result)
	{
		scheduleOnce([this](float dt){ MahjongAnim::getInstance()->playAccountZiMoAnim(); }, 1.0f, "Acc_zimo");
	}
	else if (1 == result)
	{
		scheduleOnce([this](float dt){ MahjongAnim::getInstance()->playAccountHuAnim(); }, 1.0f, "Acc_hu");
	}
	else
	{
		scheduleOnce([this](float dt){ MahjongAnim::getInstance()->playAccountGangKaiAnim(); }, 1.0f, "Acc_gangkai");
	}

	int maxId = 0;
	int maxScore = 0;
	for (int index = 0; index < 4; index++)
	{
		int newScore = players[index]->get_Score();
		if (maxScore < newScore)
		{
			maxScore = newScore;
			maxId = index;
		}
	}

	scheduleOnce([this, maxId](float dt){ panel->showBigAccountInfo(*players[maxId]); }, 1.0f, "showBigWord");
	
	scheduleOnce([this](float dt){showAccount(false); }, 10.0f, "showAccount");
}

void GameFlow::showAccount(bool isLiuJu)
{
	CCLOG("");
	CCLOG("------------------GameFlow : showAccount---------------");
	for (int index = 0; index < 4; index++)
	{
		panel->getInfoFromPlayer(*players[index]);
	}

	panel->setVisible(true);
	
	int niaoNum = isLiuJu ? -1 : 4;
	panel->showAccountInfo(niaoNum);
	Room::getInstance()->updateRoomScore();
	CCLOG("Update RoomId");
}
//------------------------------------------ 支持函数 -------------------------------------------
void GameFlow::sortCardForAll()
{
	CCLOG("GameFlow : sortCardFowAll");
	for (Player* player : players)
	{
		player->drawer->sortCard();
	}
}
