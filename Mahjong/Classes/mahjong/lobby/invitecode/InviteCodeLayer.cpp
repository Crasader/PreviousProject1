//
//  InviteCodeLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/4.
//
//

#include "mahjong/lobby/invitecode/InviteCodeLayer.hpp"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"

bool InviteCodeLayer::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto tishiBg = Sprite::create("shop/shop_bg_4.png");
    tishiBg->setPosition(640,360);
    addChild(tishiBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(InviteCodeLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(880, 540);
    addChild(closeMenu);
    
    auto title = Sprite::create("shop/invite_code_title.png");
    title->setPosition(640,530);
    addChild(title);
    
    auto codeBg = Sprite::create("shop/invite_code_bg.png");
    codeBg->setPosition(640,380);
    addChild(codeBg);
    
    auto inputBox = Sprite::create("shop/invite_code_input.png");
    inputBox->setPosition(640,405);
    addChild(inputBox);
    
    _editName = ui::EditBox::create(Size(420, 70), ui::Scale9Sprite::create());
    _editName->setPosition(Point(660, 405));
    _editName->setFont("arial", 30);
    _editName->setInputMode(cocos2d::ui::EditBox::InputMode::ANY);
    _editName->setInputFlag(cocos2d::ui::EditBox::InputFlag::SENSITIVE);
    _editName->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
    _editName->setDelegate(this);
    addChild(_editName);
    
    auto errcode = Label::createWithSystemFont("错误的邀请码", "arial", 24);
    errcode->setTag(1024);
    errcode->setColor(Color3B::RED);
    errcode->setAnchorPoint(Point::ANCHOR_MIDDLE);
    errcode->setPosition(660,350);
    addChild(errcode);
    errcode->setVisible(false);
    
    auto codeText = Sprite::create("shop/invite_code_text.png");
    codeText->setPosition(600,315);
    addChild(codeText);
    
    auto money = Label::createWithSystemFont(UserData::getInstance()->getInvitePropMoney(), "arial", 30);
    money->setColor(Color3B::YELLOW);
    money->setAnchorPoint(Point::ANCHOR_MIDDLE);
    money->setPosition(620,315);
    addChild(money);
    
    
    auto icon = Sprite::create();
    if(UserData::getInstance()->getInvitePropType() == "1"){
        icon->setTexture("mjitem/fangka_icon.png");
    }else if(UserData::getInstance()->getInvitePropType() == "2"){
        icon->setTexture("mjitem/gold_iocn.png");
    }else{
        icon->setTexture("mjitem/lequan_icon.png");
    }
    icon->setPosition(810,315);
    addChild(icon);
    
    auto propNum = Label::createWithSystemFont(StringUtils::format("X%s",UserData::getInstance()->getInvitePropNum().c_str()), "arial", 30);
    propNum->setColor(Color3B::YELLOW);
    propNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    propNum->setPosition(852,315);
    addChild(propNum);
    
    auto continueImage =  MenuItemImage::create("common/confirm_btn_1.png","common/confirm_btn_1.png",CC_CALLBACK_0(InviteCodeLayer::confirm, this));
    auto menu = Menu::create(continueImage,NULL);
    menu->setPosition(640,220);
    addChild(menu);
    
    return true;
}

void InviteCodeLayer::confirm(){
    std::string code = _editName->getText();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendInviteCodeCommand(code));
}

void InviteCodeLayer::closeView(){
    removeFromParent();
}

void InviteCodeLayer::onEnter() {
    Layer::onEnter();
    codeInviteResp = EventListenerCustom::create(MSG_INVITE_CODE_RESP, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(result == "1"){
            if(NULL != getChildByTag(1024)){
                getChildByTag(1024)->setVisible(false);
            }
            UserData::getInstance()->setInviteCodeBind(true);
            removeFromParent();
        }else{
            if(NULL != getChildByTag(1024)){
                getChildByTag(1024)->setVisible(true);
            }
        }
        
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(codeInviteResp, 1);
}


void InviteCodeLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(codeInviteResp);
}

void InviteCodeLayer::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){

    
}

void InviteCodeLayer::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){
    
}

void InviteCodeLayer::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){
    
    
}

void InviteCodeLayer::editBoxReturn(cocos2d::extension::EditBox* editBox){
    
    
}





