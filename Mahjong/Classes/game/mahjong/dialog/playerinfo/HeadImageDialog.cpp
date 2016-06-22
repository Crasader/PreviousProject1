#include "HeadImageDialog.h"
#include "UserInfo.h"
#include "NetworkManage.h"
#include "UserData.h"

bool HeadImageDialog::init(){
	if (!Layer::init()){
		
		return false;
	}
	showDialog();
	return true;
}

void HeadImageDialog::onEnter(){
	Layer::onEnter();
	changeImageListener = EventListenerCustom::create("", [=](EventCustom* event){
		char* buf = static_cast<char*>(event->getUserData());
		std::string result = buf;
		if (result == "1"){
			//TODO
		}
		else{
			//êÇ³ÆÐÞ¸ÄÊ§°Ü
		}
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(changeImageListener, 1);
}

void HeadImageDialog::onExit(){
	Layer::onExit();
}

void HeadImageDialog::showDialog(){
	MenuItem* item1 = MenuItem::create();
	item1->setContentSize(Size(1280, 720));
	Menu* menu1 = Menu::create(item1, NULL);
	this->addChild(menu1);

	auto bg = Sprite::create("playerinfo/player_info_bg.png");
	bg->setPosition(640,360);
	addChild(bg);
	auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(HeadImageDialog::closeView, this));
	auto closeMenu = Menu::create(closeImage, NULL);
	closeMenu->setPosition(870, 495);
	addChild(closeMenu);

	auto use_camara = MenuItemImage::create("playerinfo/use_phote_btn_1.png", "playerinfo/use_phote_btn_2.png",
		CC_CALLBACK_0(HeadImageDialog::useCamara,this));
	auto use_photo = MenuItemImage::create("playerinfo/from_photo_btn_1.png", "playerinfo/from_photo_btn_2.png",
		CC_CALLBACK_0(HeadImageDialog::usePhoto, this));

	Menu* menu = Menu::create(use_camara, use_photo,NULL);
	menu->setPosition(640, 360);
	menu->alignItemsVerticallyWithPadding(20);
	addChild(menu);
}

void HeadImageDialog::closeView(){
	removeFromParent();
}

void HeadImageDialog::useCamara(){

}
void HeadImageDialog::usePhoto(){ 

}


