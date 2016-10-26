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
    
    
    auto roomTitle = Sprite::create("friend/open_room_title.png");
    roomTitle->setPosition(640,570);
    addChild(roomTitle);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendRoom::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(910, 525);
    addChild(closeMenu);
    
    auto xuanze = Sprite::create("friend/xuan_ze_ju_shu.png");
    xuanze->setPosition(640,400);
    addChild(xuanze);
    
    
    auto fangka8 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectFangka8, this));
    auto fangka8Menu = Menu::create(fangka8,NULL);
    fangka8Menu->setPosition(520,420);
    addChild(fangka8Menu);
    
    auto select8 = Sprite::create("friend/icon_right.png");
    select8->setTag(1024);
    select8->setPosition(520,420);
    select8->setVisible(true);
    addChild(select8);
    
    auto kaiju8 = Sprite::create("friend/8_ju.png");
    kaiju8->setPosition(680,420);
    addChild(kaiju8);

    
    auto fangka16 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectFangka16, this));
    auto fangka16Menu = Menu::create(fangka16,NULL);
    fangka16Menu->setPosition(520,360);
    addChild(fangka16Menu);
    
    auto select16 = Sprite::create("friend/icon_right.png");
    select16->setTag(1025);
    select16->setPosition(520,360);
    select16->setVisible(false);
    addChild(select16);
    
    auto kaiju16 = Sprite::create("friend/16_ju.png");
    kaiju16->setPosition(680,360);
    addChild(kaiju16);
    
    if(UserData::getInstance()->getFangkaNum()<2){
        fangka16->setEnabled(false);
        kaiju16->setTexture("friend/16_ju_hui.png");
    }
    auto roomInfo = Sprite::create("friend/qiaoma_hua_di.png");
    roomInfo->setPosition(640,270);
    addChild(roomInfo);
    
    auto openBtn = MenuItemImage::create("mjlobby/open_room_btn_img_1.png", "mjlobby/open_room_btn_img_2.png", CC_CALLBACK_0(FriendRoom::openRoom, this));
    auto openMenu = Menu::create(openBtn,NULL);
    openMenu->setPosition(640,190);
    addChild(openMenu);
    
    return true;
}


void FriendRoom::onEnter(){
    Layer::onEnter();
    
}


void FriendRoom::onExit(){
    Layer::onExit();
    
}

void FriendRoom::openRoom(){
    if(NULL != getChildByTag(1024)){
        if(getChildByTag(1024)->isVisible()){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOpenRoomCommand("1"));
        }
    }
    if(NULL != getChildByTag(1025)){
        if(getChildByTag(1025)->isVisible()){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOpenRoomCommand("2"));
        }
    }
}



void FriendRoom::closeView(){
    removeFromParent();
}

void FriendRoom::selectFangka8(){
    if(NULL != getChildByTag(1024)){
        getChildByTag(1024)->setVisible(true);
    }
    if(NULL != getChildByTag(1025)){
        getChildByTag(1025)->setVisible(false);
    }
}

void FriendRoom::selectFangka16(){
    if(NULL != getChildByTag(1024)){
        getChildByTag(1024)->setVisible(false);
    }
    if(NULL != getChildByTag(1025)){
        getChildByTag(1025)->setVisible(true);
    }
}