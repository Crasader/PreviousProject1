#include "game/mahjong/splash/register/FindPassword.h"
#include "game/mahjong/splash/dropdownlist/DropDownListBox.h"
#include "game/mahjong/splash/dropdownlist/LoginMannger.h"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"
#include "game/mahjong/state/GameData.h"
#include "game/utils/StringUtil.h"


bool FindPassword::init(){
	if (!Layer::init()){
		return false;
	}
	showDialog();
	return true;
}

void FindPassword::onEnter(){
    Layer::onEnter();
    //用户名下拉列表
    dropListListener2 = EventListenerCustom::create("findPasswordCallBack", [=](EventCustom* event){
        _account->setText(GAMEDATA::getInstance()->getLoginAccPwd().account.c_str());
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dropListListener2, 1);
    
    findPasswordListener = EventListenerCustom::create(MSG_PLAYER_FIND_PASSWORD_RESP, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(result == "1"){
            HintDialog* dia = HintDialog::create("密码会通过短信发送到绑定手机",false);
            addChild(dia);
        }else if(result == "2"){
            HintDialog* dia = HintDialog::create("账号未绑定手机",false);
            addChild(dia);

        }else{
            HintDialog* dia = HintDialog::create("账号和绑定手机不匹配",false);
            addChild(dia);
        }
     });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(findPasswordListener, 1);
}

void FindPassword::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(dropListListener2);
    Director::getInstance()->getEventDispatcher()->removeEventListener(findPasswordListener);
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
    _account->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _account->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    _account->setDelegate(this);
    addChild(_account);
    
    
    DropDownList* drop = DropDownList::create(Sprite::create(), Size(450,240),"findPasswordCallBack");
    drop->setPosition(Point(270, 175));
    drop->setTouchAbleRect(_account->getBoundingBox());
    addChild(drop,1);
    
    auto accountHint = Sprite::create("register/accout_exist.png");
    accountHint->setPosition(600,400);
    accountHint->setTag(102);
    accountHint->setVisible(false);
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
    _phone->setInputMode(EditBox::InputMode::PHONE_NUMBER);
    _phone->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    _phone->setTag(1);
    _phone->setDelegate(this);
    addChild(_phone);


    auto imageItem = MenuItemImage::create("register/find_btn_1.png","register/find_btn_2.png",CC_CALLBACK_0(FindPassword::findPassword, this));
    Menu* menu = Menu::create(imageItem,NULL);
    menu->setTag(962);
    addChild(menu);
    menu->setPosition(640,190);
}


void FindPassword::closeView(){
	removeFromParent();
}


void FindPassword::findPassword(){
    std::string acc = _account->getText();
    if(!getChildByTag(101)->isVisible()&& acc != ""){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFindPassword(acc, _phone->getText()));
        if(NULL != getChildByTag(962)){
            ((Menu*)getChildByTag(962))->setEnabled(false);
        }
    }else{
        HintDialog* dia = HintDialog::create("请输入账号",false);
        addChild(dia);
    }
}


void FindPassword::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){
    
}


void FindPassword::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){
    if(editBox->getTag()==1){
        if(!StringUtil::checkPhone(editBox->getText())){
            if(NULL != getChildByTag(101)){
                getChildByTag(101)->setVisible(true);
            }
        }else{
            if(NULL != getChildByTag(101)){
                getChildByTag(101)->setVisible(false);
            }
        }
    }
}


void FindPassword::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){
    
    
}


void FindPassword::editBoxReturn(cocos2d::extension::EditBox* editBox){
    
    
}
