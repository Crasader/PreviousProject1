#include "Player.h"

#include "MahjongDatas.h"
#include "Rules.h"
#include "HeadPortrait.h"
#include "PlayMenu.h"
#include "MahjongAnim.h"
#include "Room.h"

Vec2 Player::lightPos = Vec2(40.0f, 30.0f);

//-----------------------------------------  �����  --------------------------------------------

//-----------------------------------------  ��ʼ��  --------------------------------------------
PlayMenu* Player::playMenu = nullptr;

Player* Player::createPlayer(PLAYER playerIndex)
{
	CCLOG("-----------------------");
	CCLOG("Player : createPlayer");
	// �½���ң�����ʼ������
	Player* player = Player::create();
	player->drawer->setDrawer(playerIndex);
	player->addHeadPortrait(playerIndex);
	if (PLAYER::PLAYER_0 == playerIndex)
	{
		player->set_CanOpera(false);
		player->set_isPlayer(true);
	}
	return player;
}

void Player::turnOnLight()
{
	CCLOG("Turn On Light ? %d", drawer->get_dir());
	if (nullptr != light)
	{
		CCLOG("Turn On Light Y");
		light->runAction(FadeIn::create(0.5f));
	}
}
void Player::turnOffLight(float dt)
{
	CCLOG("Turn Off Light ?");
	if (nullptr != light)
	{
		CCLOG("Turn Off Light Y, disPatch PlayCardEnd, GaneFlow::operaPlayEnd");
		dispatchMahjongEvent(OPERA_PLAY_END, NULL);
		light->runAction(FadeOut::create(0.5f));
	}
}

bool Player::initLogo()
{
	PLAYER dir = drawer->get_dir();
	Sprite* dirSpr;
	string dirStr = "dir_";
	if (!isZhuang)
	{
		dirStr += String::createWithFormat("%d", dir)->_string;
	}
	dirSpr = Sprite::create(dirStr + ".png");
	dirSpr->setRotation(dir * -90.0f);
	this->addChild(dirSpr);

	Size size = _director->getWinSize();
	Vec2 center = Vec2(size.width / 2, size.height / 2 + 33.0f);
	light = Sprite::create("light_" + String::createWithFormat("%d", (dir%2))->_string + ".png");
	switch (dir)
	{
	case PLAYER_0:
		light->setPosition(Vec2(center.x, center.y - lightPos.y));
		light->setRotation(180.0f);
		dirSpr->setPosition(Vec2(center.x, center.y - lightPos.y - 3.0f));
		break;
	case PLAYER_1:
		light->setPosition(Vec2(center.x + lightPos.x, center.y));
		dirSpr->setPosition(Vec2(center.x + lightPos.x + 2.0f, center.y));
		break;
	case PLAYER_2:
		light->setPosition(Vec2(center.x, center.y + lightPos.y));
		dirSpr->setPosition(Vec2(center.x, center.y + lightPos.y + 3.0f));
		break;
	case PLAYER_3:
		light->setPosition(Vec2(center.x - lightPos.x, center.y));
		light->setRotation(180.0f);
		dirSpr->setPosition(Vec2(center.x - lightPos.x - 2.0f, center.y));
		break;
	}
	light->setOpacity(0.0f);
	this->addChild(light);



	return true;
}

bool Player::init()
{
	CCLOG("Player : init");
	if (!Node::init())
	{
		return false;
	}
	set_isPlayer(false);
	set_isZhuang(false);
	set_isPickGood(false);
	set_PengPengHu(false);
	set_DaDiaoChe(false);
	set_QingYiSe(false);
	set_GangKai(false);
	set_canHu(false);
	set_Result(RESULT::NEUTRAL);
	set_NiaoNum(0);
	set_FanShu(0);
	set_Score(0);

	drawer = MahjongDrawer::create();
	this->addChild(drawer);
	return true;
}
void Player::addHeadPortrait(int dir)
{
	CCLOG("Player : addHeadPortrait %d", drawer->get_dir());
	HeadPortrait* head = HeadPortrait::create();
	int coins = Room::getInstance()->getCoins(dir);
	head->setHeadProtrait(dir, "name", dir, coins);
	this->addChild(head);
}

//-----------------------------------------  ����  --------------------------------------------
void Player::goOnOperaPick()
{
	turnOnLight();
	scheduleOnce([this](float dt){this->operaPick(); }, MahjongDrawer::timeKaiGang, "Pick__InKaiGang");
}

Card* Player::operaPick()
{
	turnOnLight();
	drawer->getName();
	CCLOG("Player %d : pick", drawer->get_dir());
	// �õ��������ƻ�ɫ
	int type;
	if (isPickGood)
	{
		type = MahjongDatas::getInstance()->popAGoodCard();
	}
	else
	{
		type = MahjongDatas::getInstance()->popACard();
	}

	Card* playedCard = drawer->drawHandCard(type);
	// ����������һ������,���ƶ�����DrawHandCard
	scheduleOnce([](float dt){dispatchMahjongEvent(OPERA_PICK_END, NULL); }, MahjongDrawer::timePickCard, "Pick");
	return playedCard;
}

void Player::operaAnGang()
{
	if (isPlayer)
	{
		playMenu->ShowAnGangButton();
	}
	else
	{
		//if (2 == drawer->get_dir() || 1 == drawer->get_dir())
		//{
		//	operaPlay();
		//	return;
		//}
		anGang();
	}
}

void Player::anGang()		// ����֮��
{
	CCLOG("Player %d: gang", drawer->get_dir());
	// ������
	scheduleOnce(CC_CALLBACK_0(Player::kaiGang, this, false), 1.0f, "KaiGang");
	scheduleOnce([this](float dt){this->operaPick(); }, MahjongDrawer::timeKaiGang, "Pick__InKaiGang");
}

void Player::operaPengGang()
{
	if (isPlayer)
	{
		playMenu->ShowGangButton();
	}
	else
	{
		pengGang();
	}
}
void Player::pengGang()
{
	turnOnLight();
	// ������
	scheduleOnce([this](float dt){this->kaiGang(true); }, 1.0f, "KaiGang");
	dispatchMahjongEvent(OPERA_PENGGANG_END, NULL);
}

//-----------------------------------------  ����  --------------------------------------------
void Player::operaPlay()
{
	CCLOG("Player %d : play", drawer->get_dir());
	if (isPlayer)	
	{	//  ��ң�ѡ�����
		set_CanOpera(true);
	}
	else				
	{	// A I ��������� 
		this->runAction(Sequence::create(DelayTime::create(random<float>(1, 2)), 
			CallFunc::create([this](){
			//playACard(drawer->cardInHand.at(random<int>(0, drawer->cardInHand.size() - 1)));

			if (drawer->cardInHand.at(0)->get_type() == 1)
			{
				playACard(drawer->cardInHand.at(0));
			}
			else
			{
				playACard(drawer->cardInHand.at(1));
			}

		}),
			NULL)); 
	}			
}
void Player::playACard(Card* card)
{
	MahjongAnim::getInstance()->playSound(SOUND::PLAYCARD);
	CCLOG("Player %d : playACard [%d]", drawer->get_dir(), card->get_type());
	// ��ס���ڴ��ƶ���û����֮ǰ����Ҫ�ر��ֶ�����Ȩ��
	set_CanOpera(false);
	// �������ϵ���һ��λ�ô���齫�����Ŵ��ƶ���
	((GameFlow*)this->getParent())->pRules->set_currentCard(drawer->drawTableCard(card));
	
	
	// ���������Ƴ��������
	drawer->cardInHand.erase(find(drawer->cardInHand.begin(), drawer->cardInHand.end(), card));
	drawer->handNode->removeChild(card, true);

	if (0 == drawer->get_dir())
	{

	}
	drawer->logHand();
	CCLOG("After Play, turnOffLight");
	scheduleOnce(CC_CALLBACK_1(Player::turnOffLight, this), MahjongDrawer::timePlayCard, "Played");
}
///////////////////
void Player::operaGang()			// ����֮��
{
	turnOnLight();
	if (isPlayer)
	{
		playMenu->ShowPengAndGang();
	}
	else
	{
		gang();
	}
}
void Player::gang()
{
	// ������
	dispatchMahjongEvent(DELETE_TABLE_BEFORE, NULL);

	scheduleOnce([this](float dt){this->kaiGang(true); }, 1.0f, "KaiGang");
	scheduleOnce([this](float dt){this->operaPick(); }, 2.0f, "Pick__InKaiGang");
}
//-----------------------------------------  ����  --------------------------------------------
void Player::operaPeng()
{
	CCLOG("player Peng");
	turnOnLight();
	if (isPlayer)
	{
		playMenu->ShowPengButton();
	}
	else
	{
		peng();
	}
}
void Player::peng()
{
	dispatchMahjongEvent(DELETE_TABLE_BEFORE, NULL);

	CCLOG("Player %d : peng", drawer->get_dir());
	// ��������
	scheduleOnce([this](float dt){kaiPeng(); }, MahjongDrawer::timePickCard, "Pick");
	scheduleOnce([this](float dt){this->operaPlay(); }, 1.0f, "Play__InKaiPeng");
}
bool Player::kaiPeng()
{
	CCLOG("Player %d : kaiPeng", drawer->get_dir());
	set_PengPengHu(true);
	drawer->drawSideCard((*drawer)[2], 3, UP);
	drawer->remove2CardInHand();
	drawer->logHand();
	return true;
}
int Player::getNewCardLocation(int type)
{
	CCLOG("Player %d : getNewCardLocation", drawer->get_dir());
	int size = drawer->cardInHand.size();
	if (0 == size || (*drawer)[0] > type)
	{
		return 0;
	}

	if ((*drawer)[size-1] <= type)
	{
		return size;
	}

	for (int i = 0; i < size - 1; i++)
	{
		if ((*drawer)[i] <= type && (*drawer)[i+1] > type)
		{
			return i + 1;
		}
	}
	return 0;
}

//-----------------------------------------  ����  --------------------------------------------
void Player::kaiGang(bool isMingGang)
{
	set_GangKai(true);

	CARD_SIDE side = isMingGang ? UP : DOWN;

	// ������or����
	if (0 == drawer->cardInSide.size())
	{	// �����ܣ����ܣ�5��
		drawer->drawSideCard((*drawer)[2], 4, side);
		if (4 == drawer->cardInHand.size())
		{
			drawer->remove3CardInHand();
		}
		else
		{
			drawer->remove4CardInHand();
		}
	}
	else
	{	// ���ܣ�2��
		drawer->drawSideCard(drawer->cardInSide.at(0)->get_type(), 4, side);
	}
	drawer->logHand();
	drawer->sortCard();
	set_GangKai(true);
}
//-----------------------------------------  ����  --------------------------------------------
void Player::operaZiMo()
{
	if (isPlayer)	//  A I ��������� 
	{
		playMenu->ShowZiMoButton();
	}
	else					// ��ң�ѡ�����
	{
		ziMo();
	}
}
void Player::ziMo()
{
	PLAYER playerIndex = drawer->get_dir();
	set_Result(ZIMO);
	CCLOG("Player[%d] : ZiMo", playerIndex);
	CCLOG("Win : %d", playerIndex);
	dispatchMahjongEvent(FLOW_NAME::OPERA_ZIMO_END, 0);
}

void Player::operaDianPao()
{
	if (isPlayer)
	{
		turnOnLight();
		playMenu->ShowDianPaoButton();
	}
	else
	{
		// ��������
		set_canHu(false);
		dispatchMahjongEvent(OPERA_DIANPAO_END, NULL);

		//dianPao();
	}
}

void Player::dianPao()
{
	CCLOG("Player[%d] : dianPao", drawer->get_dir());
	set_Result(HU);
	dispatchMahjongEvent(OPERA_DIANPAO_END, NULL);
}

void Player::operaQiangGang()
{
	if (isPlayer)
	{
		turnOnLight();
		playMenu->ShowQiangGangButton();
	}
	else
	{
		qiangGang();
	}
}

void Player::qiangGang()
{
	CCLOG("Player[%d] : qiangGang", drawer->get_dir());
	set_Result(HU);
	dispatchMahjongEvent(OPERA_QIANGGANG_END, NULL);
}

int Player::addNiaoNum()
{
	return ++NiaoNum;
}
