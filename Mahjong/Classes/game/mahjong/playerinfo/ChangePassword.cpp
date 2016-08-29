#include "game/mahjong/playerinfo/ChangePassword.h"
#include "game/mahjong/playerinfo/UserInfo.h"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"
#include "game/loading/Loading.h"
#include "game/utils/StringUtil.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"

bool ChangePassword::init(){
	if (!Layer::init()){
		
		return false;
	}
	showDialog();
	return true;
}

void ChangePassword::onEnter(){
	Layer::onEnter();
	changePwdListener = EventListenerCustom::create(MSG_CHANGE_PASSWORD_RESP, [=](EventCustom* event){
        if(NULL !=getChildByTag(6007)){
            getChildByTag(6007)->removeFromParent();
        }
        std::string result = static_cast<char*>(event->getUserData());
        if(result == "1"){
            if(newPassword != ""){
                UserData::getInstance()->setPassword(newPassword);
            }
            HintDialog* hin = HintDialog::create("密码修改成功",[=](Ref* ref){
                EventCustom ev(CLOSE_HINT_DIALOG);
                _eventDispatcher-> dispatchEvent(&ev);
            });
            addChild(hin);
        }else{
            HintDialog* hin2 = HintDialog::create("密码修改失败",[=](Ref* ref){
                EventCustom ev(CLOSE_HINT_DIALOG);
                _eventDispatcher-> dispatchEvent(&ev);
            });
            addChild(hin2);
        }
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(changePwdListener, 1);
}

void ChangePassword::onExit(){
	Layer::onExit();
	_eventDispatcher->removeEventListener(changePwdListener);
}

void ChangePassword::showDialog(){

	auto bound_phone = Sprite::create("playerinfo/password_new.png");
	bound_phone->setPosition(406,415);
	addChild(bound_phone);

	auto input_bg_1 = Scale9Sprite::create("common/input_box_bg.png");
	input_bg_1->setContentSize(Size(450, 81));
	input_bg_1->setPosition(720, 415);
	addChild(input_bg_1);
	_newPassword = EditBox::create(Size(220, 81), Scale9Sprite::create());
	_newPassword->setPosition(Point(635, 415));
	_newPassword->setTag(0);
	_newPassword->setFont("arial", 24);
	_newPassword->setDelegate(this);
    _newPassword->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _newPassword->setInputFlag(EditBox::InputFlag::PASSWORD);
    _newPassword->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	addChild(_newPassword);


	password_hint_info1 = Sprite::create("register/password_simple.png");
	password_hint_info1->setPosition(510, 355);
	password_hint_info1->setVisible(false);
	password_hint_info1->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	addChild(password_hint_info1);
	password_hint_info2 = Sprite::create("register/password_not_same.png");
	password_hint_info2->setPosition(510, 245);
	password_hint_info2->setVisible(false);
	password_hint_info2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	addChild(password_hint_info2);

	auto verification = Sprite::create("playerinfo/password_confirm.png");
	verification->setPosition(410, 305);
	addChild(verification);
	auto input_bg_2 = Scale9Sprite::create("common/input_box_bg.png");
	input_bg_2->setContentSize(Size(450, 81));
	input_bg_2->setPosition(720, 305);
	addChild(input_bg_2);
	_confirmPassword = EditBox::create(Size(230, 81), Scale9Sprite::create());
	_confirmPassword->setPosition(Point(635, 305));
	_confirmPassword->setTag(1);
	_confirmPassword->setFont("arial", 24);
	_confirmPassword->setDelegate(this);
    _confirmPassword->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _confirmPassword->setInputFlag(EditBox::InputFlag::PASSWORD);
    _confirmPassword->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	addChild(_confirmPassword);

	auto confirm = MenuItemImage::create("common/confirm_btn_1.png", "common/confirm_btn_2.png",
		CC_CALLBACK_0(ChangePassword::changePassword, this));
	auto confirmMenu = Menu::create(confirm, NULL);
	confirmMenu->setPosition(640, 180);
	this->addChild(confirmMenu);
}


void ChangePassword::changePassword(){
	std::string passwrod1 = _newPassword->getText();
	std::string passwrod2 = _confirmPassword->getText();
	if (passwrod1 != ""&&passwrod2 != ""&&!password_hint_info1->isVisible() && !password_hint_info2->isVisible()){
        newPassword = passwrod1;
		NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getChangePasswordCommand(passwrod1));
        Loading* load = Loading::create();
        load->setTag(6007);
        addChild(load);
	}
}



void ChangePassword::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){


}

void ChangePassword::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){
	if (editBox->getTag() == 0){
		if (!StringUtil::checkPassword(editBox->getText())){
			password_hint_info1->setVisible(true);
		}
		else{
			password_hint_info1->setVisible(false);
		}
	}
	else if (editBox->getTag() == 1){
		std::string passwrod1 = _newPassword->getText();
		std::string passwrod2 = _confirmPassword->getText();
		if (passwrod1 != passwrod2){
			password_hint_info2->setVisible(true);
		}
		else{
			password_hint_info2->setVisible(false);
		}
	}
}

void ChangePassword::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){


}

void ChangePassword::editBoxReturn(cocos2d::extension::EditBox* editBox){


}