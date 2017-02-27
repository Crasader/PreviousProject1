//
//  GoldNotEnoughDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/12.
//
//

#include "mahjong/shop/gold/GoldNotEnoughDialog.hpp"
#include "mahjong/lobby/goldroom/GoldRoomButton.hpp"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/shop/gold/ChargeGold.hpp"
#include "mahjong/utils/GameConfig.h"
#include "payment/android/CallAndroidMethod.h"
#include "payment/ios/IOSBridge.h"

GoldNotEnoughDialog* GoldNotEnoughDialog::create(EnterRoomResp newRespData,int type){
    GoldNotEnoughDialog* ret = new GoldNotEnoughDialog();
    if(ret &&ret->init(newRespData,type)){
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool GoldNotEnoughDialog::init( EnterRoomResp newRespData,int type){
    if(!Layer::init()){
        return false;
    }
    setRoomType(type);
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu0 = Menu::create(item1, NULL);
    this->addChild(menu0);
    
    auto dialogBg = Sprite::create("shop/gold_not_enough.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto title = Sprite::create("shop/charge/get_gold_title.png");
    title->setPosition(640, 580);
    this->addChild(title);
    
    auto bg_2 = Sprite::create("shop/first_charge_bg_2.png");
    bg_2->setPosition(645,375);
    addChild(bg_2);
    
    
    int goldShowNum =atoi(newRespData.min.c_str());
    
    auto goldNum0 = LabelAtlas::create(StringUtils::format("%d",goldShowNum>1000000?goldShowNum/10000:goldShowNum),"shop/charge/charge_num.png",21,30,'0');
    goldNum0->setScale(0.8f);
    goldNum0->setAnchorPoint(Point::ANCHOR_MIDDLE);
    goldNum0->setPosition(560,375);
    addChild(goldNum0);
    if(goldShowNum>1000000){
        auto content = Sprite::create();
        content->setTexture("shop/charge/jinbibuzhu.png");
        content->setPosition(640,400);
        addChild(content);
    }else{
        auto content_1 = Sprite::create();
        content_1->setTexture("shop/charge/jinbibuzhu_1.png");
        content_1->setPosition(640,420);
        addChild(content_1);
        auto content_2 = Sprite::create();
        content_2->setTexture("shop/charge/jinbibuzhu_2.png");
        content_2->setPosition(470,375);
        addChild(content_2);
        auto content_3 = Sprite::create();
        content_3->setTexture("shop/charge/jinbibuzhu_3.png");
        content_3->setPosition(720,375);
        addChild(content_3);
    }
    
    auto goldNum1 = LabelAtlas::create(StringUtils::format(":%s",newRespData.gold.c_str()),"shop/charge/charge_num.png",21,30,'0');
    goldNum1->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    goldNum1->setPosition(690,320);
    addChild(goldNum1);
    
    auto goldIcon = Sprite::create("shop/charge/jingbi_icon.png");
    goldIcon->setPosition(goldNum1->getPositionX()-goldNum1->getContentSize().width,315);
    goldIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    addChild(goldIcon);
    
    
    auto xuyan = Sprite::create("shop/charge/xu_yuan.png");
    xuyan->setPosition(750,320);
    addChild(xuyan);
    auto money = LabelAtlas::create(StringUtils::format("%d",atoi(newRespData.money.c_str())/100),"shop/charge/charge_num.png",21,30,'0');
    money->setPosition(760,320);
    money->setScale(0.65f);
    money->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(money);
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(GoldNotEnoughDialog::closeView, this));
    auto closeMenu = Menu::create(close, NULL);
    closeMenu->setPosition(905, 535);
    this->addChild(closeMenu);
    
    auto confirm = MenuItemImage::create("shop/charge/charge_btn_1.png", "shop/charge/charge_btn_2.png",
                                         CC_CALLBACK_0(GoldNotEnoughDialog::chargeGold, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 220);
    addChild(confirmMenu);
    
    return true;
}

void GoldNotEnoughDialog::closeView(){
    removeFromParent();
}


void GoldNotEnoughDialog::chargeGold(){
    if(UserData::getInstance()->getFangkaNum() >= getMinGoldEnterRoom(getRoomType())/40000){
        ChargeGold* gold = ChargeGold::create();
        getParent()-> addChild(gold,4);
        removeFromParent();
    }else{
        if (getRoomType() == ROOM_1){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            CallAndroidMethod::getInstance()->requestEvent(UserData::getInstance()->getPoxiaoId(), "4");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            IOSBridge::getInstance()->doPayEvent(UserData::getInstance()->getPoxiaoId(),4);
#endif
        }else if(getRoomType() == ROOM_2){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            CallAndroidMethod::getInstance()->requestEvent(UserData::getInstance()->getPoxiaoId(), "5");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            IOSBridge::getInstance()->doPayEvent(UserData::getInstance()->getPoxiaoId(),5);
#endif
        }
        else if(getRoomType() == ROOM_3){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            CallAndroidMethod::getInstance()->requestEvent(UserData::getInstance()->getPoxiaoId(), "6");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            IOSBridge::getInstance()->doPayEvent(UserData::getInstance()->getPoxiaoId(),6);
#endif
        }
    }
}

int GoldNotEnoughDialog::getMinGoldEnterRoom(int type){
    if (type == ROOM_1){
        return ENTER_ROOM_1_GOLD;
    }else if(type == ROOM_2){
        return ENTER_ROOM_2_GOLD;
        
    }else if(type == ROOM_3){
        return ENTER_ROOM_3_GOLD;
    }else {
        return 0;
    }
}
