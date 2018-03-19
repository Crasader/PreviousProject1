#include "mahjong/gameview/trusteeship/Trusteeship.h"
#include "server/NetworkManage.h"


bool Trusteeship::init(){

	if (!Layer::init()){

		return false;
	}
    MenuItem* item1 = MenuItem::create(CC_CALLBACK_0(Trusteeship::cancle, this));
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);

    auto bg = LayerColor::create(Color4B(0, 0, 0, 80), 1280, 720);
	addChild(bg, 20);
    auto tru = Sprite::create("gameview/player_tru.png");
    tru->setPosition(640,96);
    addChild(tru);
	return true;
}

void  Trusteeship::cancle(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendCancleTruCommand());
}
