#include "game/mahjong/splash/register/UserRegister.h"
#include "game/utils/StringUtil.h"
#include "server/NetworkManage.h"
#include <Regex>

bool UserRegister::init(){
	if (!BaseDialog::init()){
		return false;
	}
	return true;
}


void UserRegister::onEnter(){
	BaseDialog::onEnter();
	checkAccountListener = EventListenerCustom::create(MSG_PLAYER_CHECK_ACCOUNT, [=](EventCustom* event){
		char* buf = static_cast<char*>(event->getUserData());
		if (buf == "1"){
            account_hint_info->setTexture("register/accout_exist.png");
			account_hint_info->setVisible(true);
		}
		else{
			account_hint_info->setVisible(false);
		}
	});
	_eventDispatcher->addEventListenerWithFixedPriority(checkAccountListener, 1);
}
void UserRegister::onExit(){
	BaseDialog::onExit();
	_eventDispatcher->removeEventListener(checkAccountListener);
}

void UserRegister::drawDialog(){

	MenuItem* item1 = MenuItem::create();
	item1->setContentSize(Size(1280, 720));
	Menu* menu1 = Menu::create(item1, NULL);
	this->addChild(menu1);

//	auto all_bg = Sprite::create("common/all_bg.jpg");
//	all_bg->setPosition(640, 360);
//	addChild(all_bg);


	auto  dialogBg = Sprite::create("common/dialog_bg.png");
	dialogBg->setPosition(640, 360);
	this->addChild(dialogBg);

	auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(UserRegister::closeView, this));
	auto closeMenu = Menu::create(closeImage, NULL);
	closeMenu->setPosition(980, 580);
	addChild(closeMenu);

	auto paodai = Sprite::create("common/piaodai_zi.png");
	paodai->setPosition(640, 590);
	this->addChild(paodai);
	auto icon = Sprite::create("register/user_register_title.png");
	icon->setPosition(640, 615);
	addChild(icon);

	auto account = Sprite::create("register/account_text.png");
	account->setPosition(400, 510);
	this->addChild(account);
	auto input_bg_1 = Sprite::create("common/input_box_bg.png");
	input_bg_1->setPosition(720, 510);
	addChild(input_bg_1);
	account_input_info = Sprite::create("register/username_input_info.png");
	account_input_info->setPosition(510, 510);
	account_input_info->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	addChild(account_input_info);
	account_hint_info = Sprite::create("register/accout_exist.png");
	account_hint_info->setPosition(510, 455);
	account_hint_info->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	account_hint_info->setVisible(false);
	addChild(account_hint_info);

	_editName = EditBox::create(Size(445, 81), Scale9Sprite::create());
	_editName->setPosition(Point(720, 510));
	_editName->setTag(0);
	_editName->setFont("American Typewriter", 24);
    _editName->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	_editName->setDelegate(this);
	addChild(_editName);


	auto password = Sprite::create("register/password_text.png");
	password->setPosition(400, 395);
	this->addChild(password);
	auto input_bg_2 = Sprite::create("common/input_box_bg.png");
	input_bg_2->setPosition(720, 395);
	addChild(input_bg_2);
	password_input_info = Sprite::create("register/password_input_info.png");
	password_input_info->setPosition(510, 395);
	password_input_info->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	addChild(password_input_info);
	password_hint_info = Sprite::create("register/password_simple.png");
	password_hint_info->setPosition(510, 340);
	password_hint_info->setVisible(false);
	password_hint_info->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	addChild(password_hint_info);

	_editPwd = EditBox::create(Size(445, 81), Scale9Sprite::create());
	_editPwd->setPosition(Point(720, 395));
	_editPwd->setFont("American Typewriter", 24);
	_editPwd->setInputFlag(EditBox::InputFlag::PASSWORD);
	_editPwd->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _editPwd->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	_editPwd->setTag(1);
	_editPwd->setDelegate(this);
	addChild(_editPwd);


	auto password2 = Sprite::create("register/password_confirm_text.png");
	password2->setPosition(400, 280);
	this->addChild(password2);
	auto input_bg_3 = Sprite::create("common/input_box_bg.png");
	input_bg_3->setPosition(720, 280);
	addChild(input_bg_3);
	password_hint_info2 = Sprite::create("register/password_not_same.png");
	password_hint_info2->setPosition(510, 230);
	password_hint_info2->setVisible(false);
	password_hint_info2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	addChild(password_hint_info2);

	_editPwd2 = EditBox::create(Size(445, 81), Scale9Sprite::create());
	_editPwd2->setPosition(Point(720, 280));
	_editPwd2->setFont("American Typewriter", 24);
	_editPwd2->setInputFlag(EditBox::InputFlag::PASSWORD);
	_editPwd2->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _editPwd2->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	_editPwd2->setTag(2);
	_editPwd2->setDelegate(this);
	addChild(_editPwd2);

	auto confirm = MenuItemImage::create("common/confirm_btn_1.png", "common/confirm_btn_2.png",
		CC_CALLBACK_0(UserRegister::registerConfirm, this));
	auto confirmMenu = Menu::create(confirm, NULL);
	confirmMenu->setPosition(640, 170);
	this->addChild(confirmMenu);
}


void UserRegister::registerConfirm(){
	if (!account_hint_info->isVisible() && !password_hint_info->isVisible() && !password_hint_info2->isVisible()){
		std::string userName = _editName->getText();
		std::string passwrod = _editPwd->getText();
		NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getRegisterCommand(userName, passwrod));
		this->removeFromParent();
	}
}


void UserRegister::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){
	if (editBox->getTag() == 0){
		account_input_info->setVisible(false);
	}
	else if (editBox->getTag() == 1){
		password_input_info->setVisible(false);
	}

}

void UserRegister::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){
	if (editBox->getTag() == 0){
        if (StringUtil::checkAccount(editBox->getText())){
			NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getAccountCheckCommand(editBox->getText()));
		}
		else{
			account_hint_info->setVisible(true);
            account_hint_info->setTexture("register/accout_too_simple.png");
		}
	}
	else if (editBox->getTag() == 1){
		if (!StringUtil::checkPassword(editBox->getText())){
			password_hint_info->setVisible(true);
		}
		else{
			password_hint_info->setVisible(false);
		}
	}
	else if (editBox->getTag() == 2){
		std::string passwrod1 = _editPwd->getText();
		std::string passwrod2 = _editPwd2->getText();
		if (passwrod1 != passwrod2){
			password_hint_info2->setVisible(true);
		}
		else{
			password_hint_info2->setVisible(false);
		}
	}
}

void UserRegister::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){


}


void UserRegister::editBoxReturn(cocos2d::extension::EditBox* editBox){


}
