//
//  DiamondItem.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/13.
//
//

#include "game/mahjong/shop/fangka/ChargeItem.hpp"
#include "payment/android/CallAndroidMethod.h"
#include "payment/ios/IOSBridge.h"

#define FANGKA_NUM_1 1
#define FANGKA_NUM_2 10

ChargeItem* ChargeItem::create(int price, int fangakNum){
    
    ChargeItem* ret = new ChargeItem();
    if(ret &&ret->init(price, fangakNum)){
        
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool ChargeItem::init(int price, int fangakNum){
    if(!Sprite::init()){
        return false;
    }
    auto propBg =  Sprite::create("shop/prop_bg.png");
    propBg->setPosition(0,0);
    addChild(propBg);
    
    auto light = Sprite::create("shop/gold_bg_light.png");
    light->setPosition(0,25);
    addChild(light);
    
    auto icon_fk = Sprite::create("shop/fangka_image.png");
    icon_fk->setPosition(0,25);
    addChild(icon_fk);
    
    auto diamond = Sprite::create();
    if(fangakNum==FANGKA_NUM_1){
        diamond->setTexture("shop/fangka_num_1.png");
    }else if(fangakNum==FANGKA_NUM_2){
        diamond->setTexture("shop/fangka_num_10.png");
    }
    diamond->setPosition(0,-52);
    this->addChild(diamond,2);
    
    auto piao = Sprite::create();
    piao->setPosition(0,-65);
    addChild(piao);
    if(fangakNum==FANGKA_NUM_1){
        piao->setTexture("shop/purple_piaodai.png");
    }else if(fangakNum==FANGKA_NUM_2){
        piao->setTexture("shop/red_piaodai.png");
    }
    
    auto btnImage = MenuItemImage::create("shop/button_bg_1.png","shop/button_bg_2.png",CC_CALLBACK_1(ChargeItem::confirmCharge, this));
    if(fangakNum==FANGKA_NUM_1){
        btnImage->setTag(2);
    }else if(fangakNum==FANGKA_NUM_2){
        btnImage->setTag(3);
    }
    auto myMenu = Menu::create(btnImage,NULL);
    myMenu->setPosition(0,-118);
    addChild(myMenu);
    
    LabelAtlas* money = LabelAtlas::create(StringUtils::format("%d",price/100),"shop/prop_num.png",21,28,'0');
    money->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(money);
    
    auto yuan = Sprite::create("shop/font_yuan.png");
    yuan->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    addChild(yuan);
    
    int width2 = money->getContentSize().width + yuan->getContentSize().width;
    money->setPosition(-width2/2,-115);
    yuan->setPosition(width2/2,-115);
    
    if(fangakNum==FANGKA_NUM_2){
        auto discount = Sprite::create("shop/discount_96.png");
        discount->setPosition(70,110);
        addChild(discount);
    }
    
    
    return true;
}



void ChargeItem::confirmCharge(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*) ref;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->requestEvent(UserData::getInstance()->getPoxiaoId(),StringUtils::format("%d",temp->getTag()));//从2开始
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOSBridge::getInstance()->doPayEvent(UserData::getInstance()->getPoxiaoId(),temp->getTag());
#endif
}