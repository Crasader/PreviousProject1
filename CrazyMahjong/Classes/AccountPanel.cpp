#include "AccountPanel.h"
#include "GameScene.h"
#include "Player.h"
#include "MahjongAnim.h"
#include "Room.h"
#include "MahjongEvent.h"

Vec2 AccountPanel::typePos[4] =
{
	Vec2(400, 60),		
	Vec2(720, 240),
	Vec2(400, 420),
	Vec2(50, 240),	
};

//------------------------------- Head ---------------------------------
void AccountPanel::Head::setInfo(RESULT result, std::string scoreStr, string name, int photoID)
{
	scheduleOnce([this](float dt){
	auto posTo = this->getPosition();
	auto posFrom = posTo - Vec2(100.0f, .0f);
	this->setPosition(posFrom);
	this->setOpacity(.0f);
	auto move = EaseBackOut::create(MoveTo::create(0.5f, posTo));
	auto act = Spawn::create(move, FadeIn::create(0.5f), NULL);
		this->runAction(act);
	}, id * 0.2f, String::createWithFormat("%d", id)->_string);


	// 输赢logo--------------------------------------------------------------
	Sprite* frame;			// 背景	
	switch (result)
	{
	case HU:
	{
			   frame = Sprite::create("Account/headFrame_0.png");
			   this->addChild(frame);

			   // 头像
			   Sprite* headPhoto = Sprite::create("headPortrait_" + String::createWithFormat("%d", photoID)->_string + ".png");
			   headPhoto->setPositionY(10.0f);
			   headPhoto->setScale(0.9f);
			   this->addChild(headPhoto);
			   break;
	}
	case ZIMO:
	{
				 frame = Sprite::create("Account/headFrame_0.png");
				 this->addChild(frame);

				 // 头像
				 Sprite* headPhoto = Sprite::create("headPortrait_" + String::createWithFormat("%d", photoID)->_string + ".png");
				 headPhoto->setPositionY(10.0f);
				 headPhoto->setScale(0.9f);
				 this->addChild(headPhoto);

				 // 标识
				 Sprite* logo = Sprite::create("Account/headLogo_0.png");
				 logo->setPosition(-20, 35);
				 this->addChild(logo);
				 break;
	}
	case DIANPAO:
	{
		frame = Sprite::create("Account/headFrame_1.png");
		this->addChild(frame);

		// 头像
		Sprite* headPhoto = Sprite::create("headPortrait_" + String::createWithFormat("%d", photoID)->_string + ".png");
		headPhoto->setPositionY(10.0f);
		headPhoto->setScale(0.9f);
		this->addChild(headPhoto);

		// 标识
		Sprite* logo = Sprite::create("Account/headLogo_1.png");
		logo->setPosition(-20, 35);
		this->addChild(logo);
		break;
	}
	case LOSE:
	case NEUTRAL:
	default:
	{
		frame = Sprite::create("Account/headFrame_1.png");
		this->addChild(frame);
		// 头像
		Sprite* headPhoto = Sprite::create("headPortrait_" + String::createWithFormat("%d", photoID)->_string + ".png");
		headPhoto->setPositionY(10.0f);
		this->addChild(headPhoto);
		break;
	}
	}

	// 分数
	string labelStr = (result < 3 ? ":" : ";") + scoreStr;
	label = LabelAtlas::create(labelStr, "Account/numScore.png", 6, 9, '0');
	label->setPosition(-5.0f, -50.0f);
	this->addChild(label);
}

bool AccountPanel::Head::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}


//------------------------------- Panel --------------------------------
bool AccountPanel::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->setVisible(true);
	Vec2 center = _director->getWinSize() / 2;

	// 四个头像,113 * 150
	float dis = 20;
	float width = 113;
	Vec2 pos = Vec2(center.x - (width + dis) * 1.5, 230);

	CCLOG("AccountPanel : init");
	panel = Node::create();
	panel->setVisible(false);
	this->addChild(panel);

	// 背景模糊
	Sprite* bigBkg = Sprite::create("Account/accountBkg.jpg");
	bigBkg->setPosition(center);
	panel->addChild(bigBkg);

	Sprite* playerInfoFrame = Sprite::create("Account/playerInfoFrame.png");
	playerInfoFrame->setPosition(center.x, pos.y);
	panel->addChild(playerInfoFrame);

	Sprite* bigCoinSprite = Sprite::create("Account/coinBig.png");
	bigCoinSprite->setPosition(Vec2(center.x - 70.0f, 345.0f));
	panel->addChild(bigCoinSprite);

	for (int i = 0; i < 4; i++)
	{
		heads[i] = nullptr;
		heads[i] = Head::create();
		heads[i]->id = i;
		panel->addChild(heads[i]);
		heads[i]->setPosition(pos.x + (dis + width) * i, pos.y);
	}

	// 两个按钮
	MenuItemImage* backItem = MenuItemImage::create("Account/button_back_0.png", "Account/button_back_1.png", CC_CALLBACK_1(AccountPanel::backCallBack, this));
	backItem->setPosition(-100, -130.0f);
	MenuItemImage* againItem = MenuItemImage::create("Account/button_again_0.png", "Account/button_again_1.png", CC_CALLBACK_1(AccountPanel::againCallBack, this));
	againItem->setPosition(100, -130.0f);
	Menu* menu = Menu::create(backItem, againItem, NULL);
	panel->addChild(menu);

	wordBig = Node::create();
	wordBig->setVisible(false);
	wordBig->setPosition(400.0f, 305.0f);
	this->addChild(wordBig);
	string path = "Account/";
	wordBigFrame = addAnimNoAnimte(*wordBig, path, "WordBig_Frame");
	wordBigDaDiaoChe = addAnimNoAnimte(*wordBig, path, "WordBig_DiaoChe");
	wordBigPengPengHu = addAnimNoAnimte(*wordBig, path, "WordBig_PengPengHu");
	wordBigQingYiSe = addAnimNoAnimte(*wordBig, path, "WordBig_QingYiSe");

	wordNode = Node::create();
	wordNode->setPosition(Vec2(320.0f, 55.0f));
	wordNode->setVisible(false);
	this->addChild(wordNode);

	//
	auto posY = 20.0f;
	wordGangKai = addAnimNoAnimte(*wordNode, path, "Word_GangKai");
	wordGangKai->setVisible(false);
	wordGangKai->setPositionY(posY);

	wordDaDiaoChe = addAnimNoAnimte(*wordNode, path, "Word_DiaoChe");
	wordDaDiaoChe->setVisible(false);
	wordDaDiaoChe->setPositionY(posY);
	
	wordPengPengHu = addAnimNoAnimte(*wordNode, path, "Word_PengPengHu");
	wordPengPengHu->setVisible(false);
	wordPengPengHu->setPositionY(posY);
	
	wordQingYiSe = addAnimNoAnimte(*wordNode, path, "Word_QingYiSe");
	wordQingYiSe->setVisible(false);
	wordQingYiSe->setPositionY(posY);

	//
	wordZhongNiaoFen = addAnimNoAnimte(*wordNode, path, "Word_ZhongNiao"); 
	wordZhongNiaoFen->setVisible(false);
	wordZhongNiaoFen->setPositionX(20.0f);

	wordKuoHaoL = addAnimNoAnimte(*wordNode, path, "Word_KuoHao"); 
	wordKuoHaoL->setVisible(false);
	wordKuoHaoL->setPositionX(50.0f);

	wordNiaoShu = addAnimNoAnimte(*wordNode, path, "Word_NiaoShu");
	wordNiaoShu->setVisible(false);
	wordNiaoShu->setPositionX(70.0f);

	wordDiFen = addAnimNoAnimte(*wordNode, path, "Word_DiFen"); 
	wordDiFen->setVisible(false);
	wordDiFen->setPositionX(125.0f);

	wordKuoHaoR = addAnimNoAnimte(*wordNode, path, "Word_KuoHao");
	wordKuoHaoR->setVisible(false);
	wordKuoHaoR->setRotation(180.0f);
	wordKuoHaoR->setPositionX(185.f);
	//

	return true;
}

/*
win :

lose : 
jiangyou :
liuju:

*/

bool AccountPanel::showWord(bool isShow, Node & node, Vec2 pos)
{
	if (isShow)
	{
		auto act = Spawn::create(ScaleTo::create(0.2f, 1.0f), FadeIn::create(0.2f), NULL);
		node.setScale(3.0f);
		node.setVisible(true);
		node.setPosition(pos);
		node.setOpacity(.0f);
		node.runAction(act);
		return true;
	}
	else
	{
		node.setVisible(false);
		return false;
	}
}

void AccountPanel::showBigAccountInfo(Player & player)
{
	GangKai = player.get_GangKai();
	DaDiaoChe = player.get_DaDiaoChe();
	PengPengHu = player.get_PengPengHu();
	QingYiSe = player.get_QingYiSe();

	QingYiSe = true;

	this->player = &player;
	wordBig->setVisible(true);

	int infoNum = 3;
	infoNum -= DaDiaoChe ? 1 : 0;
	infoNum -= PengPengHu ? 1 : 0;
	infoNum -= QingYiSe ? 1 : 0;

	float startPosX = -70 + 35.0f * infoNum;
	float startPosY = wordBig->getPositionY();
	int index = 0;
	float width = 70.0f;
	if (showWord(DaDiaoChe, *wordBigDaDiaoChe, Vec2(startPosX + index * width, .0f))) { index++; }
	if (showWord(PengPengHu, *wordBigPengPengHu, Vec2(startPosX + index * width, .0f))) { index++; }
	if (showWord(QingYiSe, *wordBigQingYiSe, Vec2(startPosX + index * width, .0f))) { index++; }
	scheduleOnce([this](float dt){
		this->wordBig->setVisible(false); 
	}, 3.0f, "hideBigWord");
}

void AccountPanel::showAccountInfo(int niaoNum)
{
	panel->setVisible(true);
	if (-1 == niaoNum)
	{
		return;
	}
	wordNode->setVisible(true);

	int infoNum = 4;
	infoNum -= GangKai ? 1 : 0;
	infoNum -= DaDiaoChe ? 1 : 0;
	infoNum -= PengPengHu ? 1 : 0;
	infoNum -= QingYiSe ? 1 : 0;

	float startPosX = 25.0f * infoNum;
	int index = 0;
	//
	if (GangKai)
	{
		wordGangKai->setVisible(true);
		wordGangKai->setPositionX(startPosX);
		index++;
	}

	if (DaDiaoChe)
	{
		wordDaDiaoChe->setVisible(true);
		wordDaDiaoChe->setPositionX(startPosX + index * 50.0f);
		index++;
	}
	if (PengPengHu)
	{
		wordPengPengHu->setVisible(true);
		wordPengPengHu->setPositionX(startPosX + index * 50.0f);
		index++;
	}
	if (QingYiSe)
	{
		wordQingYiSe->setVisible(true);
		wordQingYiSe->setPositionX(startPosX + index * 50.0f);
		index++;
	}

	//
	wordZhongNiaoFen->setVisible(true);
	wordKuoHaoL->setVisible(true);
	wordNiaoShu->setVisible(true);
	wordDiFen->setVisible(true);
	wordKuoHaoR->setVisible(true);

	string numNiaoStr = String::createWithFormat("%d:", niaoNum)->_string;
	Label* numNiaoLabel = Label::createWithCharMap("Account/numZhongNiao.png", 11, 15, '0');
	numNiaoLabel->setString(numNiaoStr);
	numNiaoLabel->setPositionX(96.0f);
	wordNode->addChild(numNiaoLabel);

	int diFen = Room::getInstance()->getRoomScore();
	string diFenStr = String::createWithFormat("%d", diFen)->_string;
	Label* diFenLabel = Label::createWithCharMap("Account/numZhongNiao.png", 11, 15, '0');
	diFenLabel->setString(diFenStr);
	diFenLabel->setPositionX(170.0f);
	wordNode->addChild(diFenLabel);

	// 胡牌牌型
	Vector<Card*> cards;
	int cardNum = 0;

	for (Card* card : player->drawer->cardInHand)
	{
		auto newCard = Card::createTableCard(PLAYER_0, card->get_type());
		cards.pushBack(newCard);
		wordNode->addChild(newCard);
		newCard->setPositionY(-45.0f);
		cardNum++;
	}

	for (Card* card : player->drawer->cardInSide)
	{
		auto newCard = Card::createTableCard(PLAYER_0, card->get_type());
		cards.pushBack(newCard);
		wordNode->addChild(newCard);
		newCard->setPositionY(-45.0f);
		cardNum++;
	}
	startPosX = 80 - cardNum*14.0f;
	for (Card* card : cards)
	{
		card->setPositionX(--cardNum * 29.0f + startPosX);
	}
}

void AccountPanel::getInfoFromPlayer(Player & player)
{
	CCLOG("---------- Account : get Player[%d] info -----------", player.drawer->get_dir());
	int score = abs(player.get_Score());
	string scoreStr = String::createWithFormat("%d", score)->_string;
	auto result = player.get_Result();

	// 获得头像信息
	int headIndex = player.drawer->get_dir();
	if (nullptr != heads[headIndex])
	{
		heads[headIndex]->setInfo(result, scoreStr, "name", 0);
	}
	
	// 如果是主角，则获得主角本局信息。
	if (0 == player.drawer->get_dir())
	{
		Label* label;
		switch (result)
		{
		case HU:
		case ZIMO:
		{
			MahjongAnim::getInstance()->playWinBanner();
			label = Label::createWithCharMap("Account/numBigWin.png", 34, 42, '0');
			label->setString(scoreStr);
			label->setAdditionalKerning(-3.0f);
			label->setPosition(450.0f, 350.0f);
			label->setAnchorPoint(Vec2(0.5f, 0.5f));
			this->addChild(label);
			break;
		}
		case DIANPAO:
		case LOSE:
		{
			scoreStr = ":12345";
			label = Label::createWithCharMap("Account/numBigLose.png", 34, 42, '0');
			label->setString(scoreStr);
			label->setAdditionalKerning(-3.0f);
			label->setPosition(450.0f, 350.0f);
			label->setAnchorPoint(Vec2(0.5f, 0.5f));
			this->addChild(label);

			Sprite* logoSprite = Sprite::create("Account/logo_lose.png");
			logoSprite->setPosition(400, 410);
			this->addChild(logoSprite);

			break;
		}
		case NEUTRAL:
			Sprite* logoSprite = Sprite::create("Account/logo_jiangYou.png");
			logoSprite->setPosition(400, 410);
			this->addChild(logoSprite);
			break;
		}
	
	}
}

void AccountPanel::getAccountInfo()
{

}

void AccountPanel::backCallBack(Ref* pSender)
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	MahjongAnim::getInstance()->hideWinBanner();
	this->setVisible(false);
	_director->end();
}

void AccountPanel::againCallBack(Ref* pSender)
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
	MahjongAnim::getInstance()->hideWinBanner();
	auto instance = MahjongAnim::getInstance();
	instance->removeFromParentAndCleanup(true);
	((GameScene*)this->getParent()->getParent())->GameOver();
}









