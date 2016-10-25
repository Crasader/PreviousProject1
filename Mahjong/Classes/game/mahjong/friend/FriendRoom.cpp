#include "game/mahjong/friend/FriendRoom.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "server/NetworkManage.h"



bool FriendRoom::init()
{
    if (!Layer::init())
    {
        return false;
    }
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto dialog_bg = Sprite::create("shop/gold_not_enough.png");
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    
    auto roomTitle = Sprite::create("friend/friend_room_title.png");
    roomTitle->setPosition(640,570);
    addChild(roomTitle);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendRoom::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(910, 525);
    addChild(closeMenu);
    
    auto xuanze = Sprite::create("friend/xuan_ze_ju_shu.png");
    xuanze->setPosition(640,400);
    addChild(xuanze);
    
    
    auto roomInfo = Sprite::create("friend/qiaoma_hua_di.png");
    roomInfo->setPosition(640,270);
    addChild(roomInfo);
    
    return true;
}


void FriendRoom::onEnter(){
    Layer::onEnter();
    
}


void FriendRoom::onExit(){
    Layer::onExit();
    
}

void FriendRoom::openRoom(){

}

void FriendRoom:: enterRoom(){

}


void FriendRoom::closeView(){
    this->removeFromParent();
}