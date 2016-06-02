#include "SystemUI.h"
#include "MahjongAnim.h"

bool SystemUI::init()
{
	if (!Node::init())
	{
		return false;
	}

	Vec2 coinPos = Vec2(-230.0f, -135.0f);
	auto light = MenuItemImage::create("System_UI/GetCoinsLight.png", "System_UI/GetCoinsLight.png");
	light->setPosition(coinPos);

	auto addCoinBtn = MenuItemImage::create("System_UI/GetCoins.png", "System_UI/GetCoins.png", CC_CALLBACK_1(SystemUI::onAddCoinBtnCallBack, this));
	addCoinBtn->setPosition(coinPos);
	backBtn = MenuItemImage::create("System_UI/button_back_0.png", "System_UI/button_back_1.png", CC_CALLBACK_1(SystemUI::onBackBtnCallBack, this));
	setBtn = MenuItemImage::create("System_UI/button_set_0.png", "System_UI/button_set_1.png", CC_CALLBACK_1(SystemUI::onSetBtnCallBack, this));
	gameBtn = MenuItemImage::create("System_UI/button_moreGame_0.png", "System_UI/button_moreGame_1.png", CC_CALLBACK_1(SystemUI::onGameBtnCallBack, this));
	setPanel = SetPanel::create();
	setPanel->btn = setBtn;
	this->addChild(setPanel);

	Menu* menu = Menu::create();
	Size size = _director->getWinSize() / 2;
	backBtn->setPosition(-size.width + 30, size.height - 30);
	menu->addChild(backBtn);

	setBtn->setPosition(size.width - 30, size.height - 300);
	menu->addChild(gameBtn);

	gameBtn->setPosition(size.width - 30, size.height - 350);
	menu->addChild(setBtn);

	menu->addChild(light);
	menu->addChild(addCoinBtn);
	auto s = menu->getAnchorPoint();

	this->addChild(menu);

	Sprite* phoneNumberSpr = Sprite::create("phoneNumber.png");

	phoneNumberSpr->setPosition(700.0f, 20.0f);
	this->addChild(phoneNumberSpr);

	return true;
}

void SystemUI::onBackBtnCallBack(Ref* pSender)
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	_director->end();
	CCLOG("Exit!");
}
void SystemUI::onInforBtnCallBack(Ref* pSender)
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	CCLOG("Infor!");
}
void SystemUI::onGameBtnCallBack(Ref* pSender)
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	CCLOG("MoreGame!");
}
void SystemUI::onSetBtnCallBack(Ref* pSender)
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
	setBtn->setEnabled(false);
	setPanel->showPanel();
	CCLOG("Set!");
}

void SystemUI::onAddCoinBtnCallBack(Ref* pSender)
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
}