#include "MahjongDrawer.h"

#include "Card.h"

#include "Player.h"

#include "Rules.h";

#include "GameFlow.h"
#include "MahjongAnim.h"

//------------------------------------ 初始位置 --------------------------------------
Vec2 MahjongDrawer::cardTablePos[4] = 
{
	Vec2(340, 180),
	Vec2(500, 230),
	Vec2(460, 360),
	Vec2(300, 310),
};

Vec2 MahjongDrawer::cardSidePos[4] = 
{
	Vec2(150, 100),
	Vec2(750, 150),
	Vec2(320, 430),
	Vec2(150, 320),
};

Vec2 MahjongDrawer::cardOutHandDis[4] =
{
	Vec2(27, -30),
	Vec2(38, 26),
	Vec2(-27, 30),
	Vec2(-38, -26),
};

Vec2 MahjongDrawer::cardPickDis[4] =
{
	Vec2(20, 0),
	Vec2(0, 20),
	Vec2(-20, 0),
	Vec2(0, -20),
};

float MahjongDrawer::timePickCard = 0.1f;
float MahjongDrawer::timePlayCard = 1.0f;
float MahjongDrawer::timeKaiGang = 2.0f;

//------------------------------------  初始化  --------------------------------------
bool MahjongDrawer::init()
{
	if (!Node::init())
	{
		return false;
	}

	handNode = Node::create();
	this->addChild(handNode);

	sideNode = Node::create();
	this->addChild(sideNode);

	tableNode = Node::create();
	this->addChild(tableNode);

	return true;
}
void MahjongDrawer::setDrawer(PLAYER dir)
{
	set_dir(dir);
	switch (dir)
	{
	case PLAYER_0:
		for (int i = 0; i < 5; i++)
		{
			cardHandPos[i] = Vec2(300 + i * 66, 50);
		}
		cardBigCard[dir] = cardHandPos[2] + Vec2(.0f, 30.0f);
		cardSidePos[dir] = cardHandPos[2] + Vec2(0.0f, 0.0f);

		break;

	case PLAYER_2:
		for (int i = 0; i < 5; i++)
		{
			cardHandPos[i] = Vec2(460 - i * 38, 450);
		}
		cardBigCard[dir] = cardHandPos[2] + Vec2(.0f, -30.0f);
		cardSidePos[dir] = cardHandPos[2] + Vec2(0.0f, 0.0f);;

		break;

	case PLAYER_1:
		for (int i = 0; i < 5; i++)
		{
			cardHandPos[i] = Vec2(698, 162 + i * 40);
		}
		cardBigCard[dir] = cardHandPos[2] + Vec2(-30.0f, .0f);
		cardSidePos[dir] = cardHandPos[0] + Vec2(.0f, 60.0f);

		break;

	case PLAYER_3:
		for (int i = 0; i < 5; i++)
		{
			cardHandPos[i] = Vec2(100, 350 - i * 40);
		}
		cardBigCard[dir] = cardHandPos[2] + Vec2(30.0f, .0f);
		cardSidePos[dir] = cardHandPos[2] + Vec2(.0f, 10.0f);
		break;
	}

	
}

//-------------------------------------- 绘制 -----------------------------------------
Card* MahjongDrawer::drawHandCard(int type)
{
	int index = cardInHand.size();

	// 创建手牌
	Card* newCard = Card::createHandCard(dir, type);
	newCard->setTag(index);
	if (PLAYER::PLAYER_1 == dir){ newCard->setLocalZOrder(-index); }

	// 添加手牌，
	handNode->addChild(newCard);

	// 数据，并排序数据。
	cardInHand.push_back(newCard);
	sortData();

	// 动画
	Size size = _director->getVisibleSize();
	newCard->setPosition(size.width / 2, size.height / 2);
	newCard->runAction(MoveTo::create(timePickCard, cardHandPos[index]));
	return newCard;
}
Card* MahjongDrawer::drawTableCard(Card* card)
{
	// 牌
	int type = card->get_type();
	Card* newCard = Card::createTableCard(dir, type);
	tableNode->addChild(newCard);
	// 动画
	int index = cardInTable.size();
	int row = index % tableRow;
	int col = index / tableRow;
	if (1 == dir % 2)
	{
		swap(row, col); 
	}
	int order = (0 == dir || 3 == dir) ? index : -index;
	newCard->setLocalZOrder(order);
	Vec2 animStartPos = cardHandPos[2];
	//Vec2 animStartPos = card->getPosition();

	Vec2 posTo = Vec2(	cardTablePos[dir].x + row * cardOutHandDis[dir].x, 
									cardTablePos[dir].y + col * cardOutHandDis[dir].y);
	newCard->setPosition(animStartPos + 3 * cardPickDis[(dir+1)%4]);

	newCard->setOpacity(0.0f);
	newCard->cardFadeIn(0.5f, 0.2f, posTo, 1.0f);
	MahjongAnim::getInstance()->playPlayAnim(type, cardBigCard[dir]);
	// 记录当前打牌 
	cardInTable.push_back(newCard);
	return newCard;
}
void MahjongDrawer::drawSideCard(int type, int sideNum, CARD_SIDE side)
{
	MahjongAnim::getInstance()->playSound(SOUND::PENGGANG);
	if (PLAYER_0 != dir)
	{
		if (3 == sideNum)
		{
			MahjongAnim::getInstance()->playWordPengAnim(cardHandPos[0]);
		}
		else
		{
			MahjongAnim::getInstance()->playWordGangAnim(cardHandPos[0]);
		}
	}
	if (3 == sideNum)
	{
		MahjongAnim::getInstance()->playPengAnim(type, cardHandPos[2]);
	}
	else
	{
		MahjongAnim::getInstance()->playGangAnim (type, cardHandPos[2]);//change 1
	}

	Vec2 dis;


	switch (dir)
	{
	case PLAYER_0:
		dis = Vec2(55.0f, .0f);
		break;
	case PLAYER_1:
		dis = Vec2(.0f, cardOutHandDis[dir].y);
		break;
	case PLAYER_2:
		dis = Vec2(cardOutHandDis[dir].x, .0f);
		break;
	case PLAYER_3:
		dis = Vec2(.0f, cardOutHandDis[dir].y);
		break;
	case PLAYER_NULL:
		break;
	default:
		break;
	}

	for (int i = 0; i < sideNum; i++)
	{
		Card* newCard = Card::createSideCard(dir, side, type);

		newCard->setLocalZOrder(dir == 3 ? -i : i);

		Vec2 posTo = Vec2(	cardSidePos[dir].x - i * dis.x,
											cardSidePos[dir].y - i * dis.y);
		newCard->setPosition(posTo);
		sideNode->addChild(newCard);

		cardInSide.push_back(newCard);
	}// end for
	sideNode->setVisible(false);
	scheduleOnce([this](float dt){
		this->sideNode->setVisible(true);
	}, 2.15f, "addSideCard");
}

//--------------------------------------- 移除 ----------------------------------------
void MahjongDrawer::remove4CardInHand()
{
	int index;
	// 判断移除前4张or后4张
	if ((*this)[3] == (*this)[4]){ index = 1; }
	else{ index = 0; }

	// 移除4张手牌。
	for (int i = 0; i < 4; i++)
	{
		handNode->removeChild(cardInHand.at(index));
		cardInHand.erase(cardInHand.begin() + index);
	}

	cardHandPos[0] = cardHandPos[3];
	cardHandPos[1] = cardHandPos[4];
}

void MahjongDrawer::remove3CardInHand()
{
	int index;
	// 判断移除前3张or后3张
	if ((*this)[0] == (*this)[1]){ index = 0; }
	else{ index = 1; }

	// 移除4张手牌。
	for (int i = 0; i < 3; i++)
	{
		handNode->removeChild(cardInHand.at(index));
		cardInHand.erase(cardInHand.begin() + index);
	}

	cardHandPos[0] = cardHandPos[3];
	cardHandPos[1] = cardHandPos[4];
}

void MahjongDrawer::remove2CardInHand()
{
	int index;
	// 判断移除前3张or后3张
	if ((*this)[0] == (*this)[1])
	{
		index = 0; 
	}
	else if ((*this)[1] == (*this)[2])
	{
		index = 1; 
	}
	else
	{
		index = 2;
	}

	// 移除4张手牌。
	for (int i = 0; i < 2; i++)
	{
		handNode->removeChild(cardInHand.at(index));
		cardInHand.erase(cardInHand.begin() + index);
	}

	cardHandPos[0] = cardHandPos[3];
	cardHandPos[1] = cardHandPos[4];
}
void MahjongDrawer::remove1CardInHand()
{
	// 判断移除前1张or后1张
	if ((*this)[0] == cardInSide[0]->get_type())
	{	
		handNode->removeChild(cardInHand[0]);
		cardInHand.erase(cardInHand.begin());
	}
	else
	{
		// 第二张。
		handNode->removeChild(cardInHand[1]);
		cardInHand.pop_back();
	}
}

void MahjongDrawer::remove1CardInTable()
{
	removeChild(cardInTable.at(cardInTable.size() - 1));
	// 从玩家桌牌列表中移除桌牌数据
	cardInTable.pop_back();
}

// 根据花色升序排序
bool sortByType(Card* card1, Card* card2)
{
	return card2->get_type() > card1->get_type();
}
void MahjongDrawer::sortData()
{
	std::sort(cardInHand.begin(), cardInHand.end(), sortByType);
	logHand();
}
void MahjongDrawer::sortCard()
{
	if (1 == cardInHand.size())
	{
		cardInHand[0]->runAction(MoveTo::create(1.0f, cardHandPos[0]));
		return;
	}

	for (int i = 0; i < cardInHand.size(); i++)
	{
		if (cardInHand[i]->getPosition() != cardHandPos[i])
		{
			cardInHand[i]->runAction(MoveTo::create(random<float>(0.2f, 0.8f), cardHandPos[i]));
		}
		cardInHand[i]->setLocalZOrder(PLAYER::PLAYER_1 == dir ? -i : i);
	}
}

void MahjongDrawer::logHand()
{
	string cardstr = "Player " + String::createWithFormat("%d", dir)->_string + " : ";
	for (Card* card : cardInHand)
	{
		cardstr += String::createWithFormat("%d", card->get_type())->_string;
		cardstr += "  ";
	}
	CCLOG(cardstr.c_str());
}
