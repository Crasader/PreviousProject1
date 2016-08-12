#include "game/mahjong/chat/GameChat.h"
#include "game/mahjong/chat/PlayerChat.h"

bool GameChat::init(){
	if (!Layer::init()){
		return false;
	}
	drawDialog();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameChat::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,
		this);
	return true;
}

void GameChat::drawDialog(){
	auto chatBg = Sprite::create("chat/chat_text_box.png");
	chatBg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	chatBg->setPosition(5,0);
	this->addChild(chatBg);

	auto faceOnMenuItem = MenuItemImage::create("chat/face_btn_1.png", "chat/face_btn_1.png");
	auto faceOffMenuItem = MenuItemImage::create("chat/face_btn_2.png", "chat/face_btn_2.png");
	faceToggleMenuItem = MenuItemToggle::createWithTarget(this,
		menu_selector(GameChat::faceToggleCallback),
		faceOnMenuItem, faceOffMenuItem, NULL);
	faceToggleMenuItem->setSelectedIndex(1);
	auto textOnMenuItem = MenuItemImage::create("chat/text_btn_1.png", "chat/text_btn_1.png");
	auto textOffMenuItem = MenuItemImage::create("chat/text_btn_2.png", "chat/text_btn_2.png");
	textToggleMenuItem = MenuItemToggle::createWithTarget(this,
		menu_selector(GameChat::textToggleCallback),
		textOnMenuItem, textOffMenuItem, NULL);
	textToggleMenuItem->setSelectedIndex(0);
	Menu* menu = Menu::create(faceToggleMenuItem, textToggleMenuItem, NULL);
	menu->alignItemsHorizontallyWithPadding(5);
	menu->setPosition(160, 30);
	this->addChild(menu);

	addAllFace();
}

void GameChat::faceToggleCallback(Ref* psend){
	faceToggleMenuItem->setSelectedIndex(1);
	textToggleMenuItem->setSelectedIndex(0);
}


void GameChat::textToggleCallback(Ref* psend){
	faceToggleMenuItem->setSelectedIndex(0);
	textToggleMenuItem->setSelectedIndex(1);
}

void GameChat::addAllFace(){
	faceMenu = Menu::create();
	for (int i = 0; i < 23; i++){
		std::string image_name = cocos2d::String::createWithFormat("chat/face_%d.png",i+1)->_string;
		MenuItemImage* face = MenuItemImage::create(image_name, image_name, CC_CALLBACK_1(GameChat::faceSelected,this));
		faceMenu->addChild(face);
		face->setTag(i+1);
		face->setPosition(38 + 50 * (i%6), 225-i/6*50);
	}
	faceMenu->setPosition(0,0);
	this->addChild(faceMenu);
}


void GameChat::faceSelected(Ref* ref){
	MenuItemImage* temp = (MenuItemImage*)ref;
	PlayerChat* pl = PlayerChat::create();
	pl->showPlayerChat(text,2,2);
	this->addChild(pl);
}

void GameChat::isShowFace(bool show){
	faceMenu->setVisible(false);
}

bool GameChat::onTouchBegan(Touch *touch, Event  *event){
	if (this->isVisible()){
		this->setVisible(false);
		return true;
	}
	else{
		return false;
	}
	
}


