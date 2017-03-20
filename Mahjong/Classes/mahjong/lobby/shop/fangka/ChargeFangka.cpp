//
//  ChargeDiamond.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/18.
//
//

#include "mahjong/lobby/shop/fangka/ChargeFangka.hpp"
#include "mahjong/lobby/shop/ShopHintDialog.hpp"
#include "mahjong/lobby/shop/fangka/ChargeItem.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/loading/Loading.h"
#include "mahjong/common/utils/StringUtil.h"
#include "payment/android/CallAndroidMethod.h"
#include "payment/ios/IOSBridge.h"
#include "server/NetworkManage.h"


bool ChargeFangka::init(){
    
    if(!Layer::init()){
        
        return false;
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFangkaChargeListCommand());
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto dialog_bg = ui::Scale9Sprite::create("shop/gold_not_enough.png",Rect(0, 0, 639, 444), Rect(100, 0, 100, 0));
    dialog_bg->setTag(1024);
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/charge_title.png");
    title->setPosition(640,560);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ChargeFangka::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(910, 540);
    closeMenu->setTag(1025);
    addChild(closeMenu);
    
    Loading* lod = Loading::create(true);
    lod->setTag(1000);
    addChild(lod);
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
    //按价格排序
    if(list.list.size()>0){
        for(int i=0; i<list.list.size()-1;i++){
            if(list.list.at(i).money>list.list.at(i+1).money){
                swap(list.list.at(i), list.list.at(i+1));
            }
        }
    }
    if(NULL != getChildByTag(1025)){
        int width2 = (list.list.size()-2)*140;
        getChildByTag(1025)->setPosition(getChildByTag(1025)->getPosition().x+width2/2,getChildByTag(1025)->getPosition().y);
    }
    if(NULL != getChildByTag(1024)){
        int width = (list.list.size()-2)*140;
        getChildByTag(1024)->setContentSize(Size(640+(width>0?width:0),444));
    }
    for(int i=0;i<list.list.size();i++){
        int posx = (1280-(list.list.size()-1)*230)/2;
        ChargeItem* item = ChargeItem::create(list.list.at(i).money, list.list.at(i).fangka,list.list.at(i).payId);
        item->setPosition(posx+230*i,345);
        addChild(item);
    }
}

void ChargeFangka::closeView(){
    removeFromParent();
}
