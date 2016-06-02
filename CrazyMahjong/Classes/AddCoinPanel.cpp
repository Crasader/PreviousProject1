#include "AddCoinPanel.h"
#include "MahjongEvent.h"
#include "Room.h"
#include "MahjongAnim.h"

bool AddCoinPanel::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->setVisible(false);

	Sprite* frame = Sprite::create("AddCoin/AddCoinFrame.png");
	this->addChild(frame);

	Menu* menu = Menu::create();
	menu->ignoreAnchorPointForPosition(true);
	menu->setPosition(.0f, .0f);
	this->addChild(menu);

	std::string strBkg = "AddCoin/AddCoinWordBkg.png";
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			int index = i * 2 + j;
			MenuItemImage* bkg = MenuItemImage::create(strBkg, strBkg, [index](Ref* pSender){ CCLOG("--------------  add Coin : %d ---------------", index); });
			menu->addChild(bkg);
			float dx = 120;
			float dy = 50;
			float xx = 0 == j ? -dx : dx;
			float yy = 0 == i ? dy : -dy;
			bkg->setPosition(xx, yy - 30.0f);
			
			Sprite* word = Sprite::create(String::createWithFormat("AddCoin/AddCoinWord_%d.png", index)->_string);
			word->ignoreAnchorPointForPosition(true);
			bkg->addChild(word);
		}
	}

	this->setPosition(400.0f, 240.0f);

	return true;
}

void AddCoinPanel::showPanel()
{
	this->setScale(.0f);
	this->setVisible(true);
	this->runAction(ScaleTo::create(time, 1.0f));
}
void AddCoinPanel::hidePanel()
{
	this->runAction(Sequence::create(ScaleTo::create(time, .0f), [this](){this->setVisible(false); }, NULL));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ChooseTimesPanel::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->setVisible(false);

	Sprite* frame = Sprite::create("Choose/Frame.png");
	this->addChild(frame);

	Menu* menu = Menu::create();
	menu->ignoreAnchorPointForPosition(true);
	menu->setPosition(.0f, .0f);
	this->addChild(menu);

	for (int index = 0; index < 4; ++index)
	{
		std::string str = String::createWithFormat("Choose/Times_%d.png", index)->_string;
		MenuItemImage* bkg = MenuItemImage::create(str, str, [this, index](Ref* pSender){ 
			MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

			Room::getInstance()->setRoomTimes(pow(2, index));
			dispatchMahjongEvent(DEALCARDS, NULL);
			hidePanel();
			CCLOG("--------------  chooseTimes : %d ---------------", index); });
		bkg->setPosition(-150.0f + index * 100.0f, .0f);
		menu->addChild(bkg);
	}
	Sprite* word = Sprite::create(String::createWithFormat("Choose/Wait.png")->_string);
	word->ignoreAnchorPointForPosition(true);
	word->setPosition(-170.0f, -120.0f);
	this->addChild(word);

	this->setPosition(400.0f, 240.0f);
	showPanel();
	return true;
}

void ChooseTimesPanel::showPanel()
{
	this->setScale(.0f);
	this->setVisible(true);
	this->runAction(ScaleTo::create(time, 1.0f));
}
void ChooseTimesPanel::hidePanel()
{
	this->runAction(Sequence::create(ScaleTo::create(time, .0f), [this](){this->setVisible(false); }, NULL));
}