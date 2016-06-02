#include "game/mahjong/dialog/register/FindPassword.h"

bool FindPassword::init(){
	if (!Layer::init()){
		return false;
	}
	showDialog();
	return true;
}


void FindPassword::showDialog(){
	MenuItem* item1 = MenuItem::create();
	item1->setContentSize(Size(1280, 720));
	Menu* menu1 = Menu::create(item1, NULL);
	this->addChild(menu1);

	auto all_bg = Sprite::create("common/all_bg.jpg");
	all_bg->setPosition(640, 360);
	addChild(all_bg);


	auto  dialogBg = Sprite::create("common/dialog_bg.png");
	dialogBg->setPosition(640, 360);
	this->addChild(dialogBg);

	auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FindPassword::closeView, this));
	auto closeMenu = Menu::create(closeImage, NULL);
	closeMenu->setPosition(980, 580);
	addChild(closeMenu);

	auto paodai = Sprite::create("common/piaodai_zi.png");
	paodai->setPosition(640, 590);
	this->addChild(paodai);
	auto icon = Sprite::create("register/find_pwd.png");
	icon->setPosition(640, 615);
	addChild(icon);
    
    auto account = Sprite::create("register/find_acoount_text.png");
    account->setPosition(400, 450);
    this->addChild(account);
    auto input_bg_1 = Sprite::create("common/input_box_bg.png");
    input_bg_1->setPosition(720, 450);
    addChild(input_bg_1);

    
    _account = EditBox::create(Size(445, 81), Scale9Sprite::create());
    _account->setPosition(Point(720, 450));
    _account->setTag(0);
    _account->setFont("American Typewriter", 24);
    _account->setDelegate(this);
    addChild(_account);
    
    
    auto accountHint = Sprite::create("register/accout_exist.png");
    accountHint->setPosition(600,400);
    accountHint->setTag(102);
    addChild(accountHint);
    
    
    auto password = Sprite::create("register/phone_text.png");
    password->setPosition(400, 335);
    this->addChild(password);
    auto input_bg_2 = Sprite::create("common/input_box_bg.png");
    input_bg_2->setPosition(720, 335);
    addChild(input_bg_2);
    
    auto phoneHint = Sprite::create("playerinfo/phone_error_hint.png");
    phoneHint->setPosition(605,280);
    phoneHint->setVisible(false);
    phoneHint->setTag(101);
    addChild(phoneHint);

    
    _phone = EditBox::create(Size(445, 81), Scale9Sprite::create());
    _phone->setPosition(Point(720, 335));
    _phone->setFont("American Typewriter", 24);
    _phone->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _phone->setTag(1);
    _phone->setDelegate(this);
    addChild(_phone);


    auto imageItem = MenuItemImage::create("register/find_btn_1.png","register/find_btn_2.png",CC_CALLBACK_0(FindPassword::findPassword, this));
    Menu* menu = Menu::create(imageItem,NULL);
    addChild(menu);
    menu->setPosition(640,190);
}


void FindPassword::closeView(){
	removeFromParent();
}


void FindPassword::findPassword(){
    
}


void FindPassword::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){
    
}


void FindPassword::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){
   
}


void FindPassword::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){
    
    
}


void FindPassword::editBoxReturn(cocos2d::extension::EditBox* editBox){
    
    
}
