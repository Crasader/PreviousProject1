#include "game/mahjong/friend/FriendRoom.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "server/NetworkManage.h"
#include "game/mahjong/widget/HeadImage.hpp"
#include "game/mahjong/friend/MahjongNumberKeypads.hpp"



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
    
    auto dialog_bg = Sprite::create("shop/shop_bg.png");
    dialog_bg->setScale(0.9f);
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    auto  dialogBg = Sprite::create("friend/friend_room_bg.jpg");
    dialogBg->setPosition(640, 330);
    this->addChild(dialogBg);
    
    auto roomTitle = Sprite::create("friend/friend_room_title.png");
    roomTitle->setPosition(640,610);
    addChild(roomTitle);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendRoom::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1000, 570);
    addChild(closeMenu);
    
    auto openImage = MenuItemImage::create("friend/open_room_btn_1.png","friend/open_room_btn_2.png",CC_CALLBACK_0(FriendRoom::openRoom, this));
    auto enterImage = MenuItemImage::create("friend/enter_room_btn_1.png","friend/enter_room_btn_2.png",CC_CALLBACK_0(FriendRoom::enterRoom, this));
    Menu* openBtn = Menu::create(openImage,enterImage,NULL);
    openBtn->alignItemsVerticallyWithPadding(20);
    openBtn->setPosition(730,300);
    addChild(openBtn);
    
    return true;
}


void FriendRoom::onEnter(){
    Layer::onEnter();
    
}


void FriendRoom::onExit(){
    Layer::onExit();
    
}

void FriendRoom::openRoom(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOpenRoomCommand(""));
    this->removeFromParent();
}

void FriendRoom:: enterRoom(){
    MahjongNumberKeypads* keypads = MahjongNumberKeypads::create();
    addChild(keypads);
}


void FriendRoom::closeView(){
    this->removeFromParent();
}