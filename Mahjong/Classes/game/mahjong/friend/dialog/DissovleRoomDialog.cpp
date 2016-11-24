//
//  HintDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/7.
//
//

#include "game/mahjong/friend/dialog/DissovleRoomDialog.hpp"
#include "server/NetworkManage.h"
#include "game/mahjong/state/GameData.h"


bool DissovleRoomDialog::init(){
    if(!Layer::init()){
        return false;
    }
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto dialogBg = Sprite::create("common/dialog_bg_small.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto title = Sprite::create("common/tishi_icon.png");
    title->setPosition(640, 500);
    this->addChild(title);
    
    auto thishiBg = Sprite::create("common/thishi_bg.png");
    thishiBg->setPosition(640, 375);
    addChild(thishiBg);
    
    nickNameText = Label::createWithSystemFont("", "Arial", 30);
    nickNameText->setColor(Color3B(38,158,228));
    nickNameText->setPosition(640, 360);
    addChild(nickNameText);
    
    
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",CC_CALLBACK_0(DissovleRoomDialog::closeView, this));
    auto closeMenu = Menu::create(close, NULL);
    
    
    closeMenu->setPosition(860, 490);
    this->addChild(closeMenu);
    
    auto confirm = MenuItemImage::create("friend/agree_btn_1.png", "friend/agree_btn_2.png",
                                         CC_CALLBACK_0(DissovleRoomDialog::agree, this));
    auto disagree = MenuItemImage::create("friend/dis_agree_btn_1.png", "friend/dis_agree_btn_2.png",
                                          CC_CALLBACK_0(DissovleRoomDialog::disAgree, this));
    auto confirmMenu = Menu::create(confirm,disagree, NULL);
    confirmMenu->alignItemsHorizontallyWithPadding(5);
    confirmMenu->setPosition(640, 240);
    addChild(confirmMenu);
    schedule([=](float dt){
        agree();
    }, 0, 0,60,"paopaotang");
    return true;
}

void DissovleRoomDialog::setNickName(std::string msg){
    nickNameText->setString(StringUtils::format("%s申请解散房间",msg.c_str()));
}

void DissovleRoomDialog::agree(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDissolveRoomSelectCommand("1"));
    removeFromParent();
}

void DissovleRoomDialog::disAgree(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDissolveRoomSelectCommand("0"));
    removeFromParent();
}

void DissovleRoomDialog::closeView(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDissolveRoomSelectCommand("0"));
    removeFromParent();
}
