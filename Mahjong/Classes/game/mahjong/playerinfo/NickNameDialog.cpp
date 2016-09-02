#include "game/mahjong/playerinfo/NickNameDialog.h"
#include "game/mahjong/playerinfo/UserInfo.h"
#include "game/loading/Loading.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"

bool NickNameDialog::init(){
	if (!Layer::init()){
		
		return false;
	}
	showDialog();
	return true;
}

void NickNameDialog::onEnter(){
	Layer::onEnter();
	checkNickName = EventListenerCustom::create("", [=](EventCustom* event){
			
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(checkNickName, 1);

	changeNicknameListener = EventListenerCustom::create(MSG_CHANGE_NICKNAME_RESP, [=](EventCustom* event){
		char* buf = static_cast<char*>(event->getUserData());
		std::string result = buf;
        if(NULL != getChildByTag(199)){
            getChildByTag(199)->removeFromParent();
        }
		if (result == "1"){
			std::string nickname = _editName->getText();
			UserData::getInstance()->setNickName(nickname);
			UserData::getInstance()->setChangeName(true);
			((UserInfo*)getParent())->updateNickname();
			this->removeFromParent();
		}
		else if (result == "2"){
			nickNameHintInfo->setTexture("playerinfo/nickname_hint.png");
			nickNameHintInfo->setVisible(true);
		}
		else{
			nickNameHintInfo->setTexture("playerinfo/nickname_hint_2.png");
			nickNameHintInfo->setVisible(true);
		}
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(changeNicknameListener, 1);
}

void NickNameDialog::onExit(){
	Layer::onExit();
	_eventDispatcher->removeEventListener(checkNickName);
	_eventDispatcher->removeEventListener(changeNicknameListener);
}

void NickNameDialog::showDialog(){
	MenuItem* item1 = MenuItem::create();
	item1->setContentSize(Size(1280, 720));
	Menu* menu1 = Menu::create(item1, NULL);
	this->addChild(menu1);

	auto bg = Sprite::create("playerinfo/player_info_bg.png");
	bg->setPosition(640,360);
	addChild(bg);
	auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(NickNameDialog::closeView, this));
	auto closeMenu = Menu::create(closeImage, NULL);
	closeMenu->setPosition(870, 495);
	addChild(closeMenu);

	auto input_bg_1 = Scale9Sprite::create("common/input_box_bg.png");
	input_bg_1->setContentSize(Size(430, 81));
	input_bg_1->setPosition(640, 400);
	addChild(input_bg_1);
	_editName = EditBox::create(Size(410, 81), Scale9Sprite::create());
	_editName->setPosition(Point(640, 400));
	_editName->setTag(0);
	_editName->setFont("arial", 24);
    _editName->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
    _editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	_editName->setDelegate(this);
	addChild(_editName);
	nickNameHintInfo = Sprite::create();
	nickNameHintInfo->setPosition(640,340);
	nickNameHintInfo->setVisible(false);
	addChild(nickNameHintInfo);

	auto editBtn1 = MenuItemImage::create("playerinfo/clear_btn_1.png", "playerinfo/clear_btn_1.png",
		CC_CALLBACK_0(NickNameDialog::clearInput, this));
	Menu* menu2 = Menu::create(editBtn1, NULL);
	menu2->setPosition(815, 400);
	addChild(menu2);

	auto confirm = MenuItemImage::create("common/confirm_btn_1.png", "common/confirm_btn_2.png",
		CC_CALLBACK_0(NickNameDialog::changeNickName, this));
	auto confirmMenu = Menu::create(confirm, NULL);
	confirmMenu->setPosition(640, 260);
	this->addChild(confirmMenu);
}

void NickNameDialog::closeView(){
	removeFromParent();
}

void NickNameDialog::clearInput(){
	_editName->setText("");
}

void NickNameDialog::changeNickName(){
	std::string nickName = _editName->getText();
		if (nickName != ""){
			Loading* loading = Loading::create();
            loading->setTag(199);
			addChild(loading);
			NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getChangeNickNameCommand(nickName));
		}
}

//ø™ ºΩ¯»Î±‡º≠
void NickNameDialog::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){


}
//Ω· ¯±‡º≠
void NickNameDialog::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){

}
//±‡º≠øÚŒƒ±æ∏ƒ±‰
void NickNameDialog::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){


}
//µ±¥•∑¢return∫Ûµƒªÿµ˜∫Ø ˝
void NickNameDialog::editBoxReturn(cocos2d::extension::EditBox* editBox){


}