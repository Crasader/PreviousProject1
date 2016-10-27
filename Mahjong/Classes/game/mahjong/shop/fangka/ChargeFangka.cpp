//
//  ChargeDiamond.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/18.
//
//

#include "game/mahjong/shop/fangka/ChargeFangka.hpp"
#include "game/mahjong/shop/ShopHintDialog.hpp"
#include "game/mahjong/shop/fangka/ChargeItem.hpp"
#include "game/mahjong/state/GameData.h"
#include "game/loading/Loading.h"
#include "game/utils/StringUtil.h"
#include "payment/android/CallAndroidMethod.h"
#include "payment/ios/IOSBridge.h"
#include "server/NetworkManage.h"


bool ChargeFangka::init(){
    
    if(!Layer::init()){
        
        return false;
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDiamondChangeListCommand());
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto dialog_bg = Sprite::create("shop/charge_bg.png");
    dialog_bg->setPosition(640,360);
    dialog_bg->setScaleX(0.8f);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/charge_title.png");
    title->setPosition(654,560);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ChargeFangka::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(960, 550);
    addChild(closeMenu);
    
    if(!GAMEDATA::getInstance()->getFangkaChargeList().needInit){
        Loading* lod = Loading::create(true);
        lod->setTag(1000);
        addChild(lod);
    }else{
        showChargeDialog();
    }
    
    return true;
    
}


void ChargeFangka::onEnter(){
    Layer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_GOLD_CHANGE_LIST, [=](EventCustom* event){
        if(NULL != getChildByTag(1000)){
            getChildByTag(1000)->removeFromParent();
        }
        showChargeDialog();
    });
}

void ChargeFangka::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(MSG_PLAYER_GOLD_CHANGE_LIST);
}

void ChargeFangka::showChargeDialog(){
    FangkaChargeList list = GAMEDATA::getInstance()->getFangkaChargeList();
    for(int i=0;i<list.list.size();i++){
        ChargeItem* item = ChargeItem::create(list.list.at(i).money, list.list.at(i).fangka);
        item->setPosition(415+220*i,345);
        addChild(item);
    }
}

void ChargeFangka::closeView(){
    removeFromParent();
    
}