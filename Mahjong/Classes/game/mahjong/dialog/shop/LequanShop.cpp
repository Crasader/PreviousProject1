//
//  LequanShop.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#include "game/mahjong/dialog/shop/LequanShop.hpp"
#include "game/mahjong/dialog/shop/ExchangePropCell.hpp"
#include "game/mahjong/state/GameData.h"
#include "game/loading/Loading.h"
#include "server/NetworkManage.h"
#include "game/utils/StringUtil.h"
#include "userdata/UserData.h"
#include "game/mahjong/dialog/shop/ShopHintDialog.hpp"

bool LequanShop::init(){
    if(!Layer::init()){
        
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto all_bg = Sprite::create("common/all_bg.jpg");
    all_bg->setPosition(640, 360);
    addChild(all_bg);
    
    auto dialog_bg = Sprite::create("shop/shop_bg.png");
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/title_shop.png");
    title->setPosition(654,660);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(LequanShop::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1050, 610);
    addChild(closeMenu);
    
    if(GAMEDATA::getInstance()->getLequanChangeList().list.size()==0){
        Loading* lod = Loading::create(true);
        lod->setTag(1000);
        addChild(lod);
    }else{
        showLequanShop();
    }
    return true;
}


void LequanShop::onEnter(){
    Layer::onEnter();
    lequanChangeList = EventListenerCustom::create(MSG_PLAYER_LEQUAN_CHANGE_LIST, [=](EventCustom* event){
        if(NULL != getChildByTag(1000)){
            getChildByTag(1000)->removeFromParent();
            showLequanShop();
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(lequanChangeList, 1);
    
}

void LequanShop::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(lequanChangeList);
//    _eventDispatcher->removeEventListener(goldChangeResp);
}

void LequanShop::showLequanShop(){
    
    auto btnBg = Sprite::create("shop/record_btn_bg.png");
    btnBg->setPosition(640,570);
    addChild(btnBg);
    
    auto recordImage = MenuItemImage::create("shop/exchange_record_1.png","shop/exchange_record_1.png",CC_CALLBACK_0(LequanShop::showRecord, this));
    recordImage->setScale(0.7f);
    auto recordMenu = Menu::create(recordImage, NULL);
    recordMenu->setPosition(272,572);
    addChild(recordMenu);
    
    auto lequanIcon = Sprite::create("shop/lequan_icon.png");
    lequanIcon->setPosition(385,572);
    addChild(lequanIcon);
    
    LabelAtlas* lequanNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d",UserData::getInstance()->getTicket())->_string,"shop/prop_num.png",21,28,'0');
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lequanNum->setPosition(416,572);
    addChild(lequanNum);
    
    for(int i=0;i<GAMEDATA::getInstance()->getLequanChangeList().list.size();i++){
        ExchangePropCell* cell = ExchangePropCell::create(atoi(GAMEDATA::getInstance()->getLequanChangeList().list.at(i).propId.c_str()), atoi(GAMEDATA::getInstance()->getLequanChangeList().list.at(i).propPrice.c_str()),GAMEDATA::getInstance()->getLequanChangeList().list.at(i).propName);
        cell->setPosition(312+(i%4)*220,435-(i/4)*230);
        addChild(cell);
    }
}


void LequanShop::exchange(Ref* ref){
    
    
    
}

void LequanShop::showRecord(){
    
    
    
    
}

void  LequanShop:: closeView(){
    
    removeFromParent();
}