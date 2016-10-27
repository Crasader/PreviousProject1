//
//  DiamondItem.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/13.
//
//

#include "game/mahjong/shop/fangka/DiamondItem.hpp"
#include "payment/android/CallAndroidMethod.h"
#include "payment/ios/IOSBridge.h"

#define DIAMOND_NUM_1 50
#define DIAMOND_NUM_2 500

DiamondItem* DiamondItem::create(int price, int diamondNum){
    
    DiamondItem* ret = new DiamondItem();
    if(ret &&ret->init(price, diamondNum)){
        
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool DiamondItem::init(int price, int diamondNum){
    if(!Sprite::init()){
        return false;
    }
    auto propBg =  Sprite::create("shop/prop_bg.png");
    propBg->setPosition(0,0);
    addChild(propBg);
    
    auto light = Sprite::create("shop/diamond_bg.png");
    light->setPosition(0,25);
    addChild(light);

    auto diamond = Sprite::create();
    if(diamondNum==DIAMOND_NUM_1){
        diamond->setTexture("shop/diamond_icon_2.png");
    }else if(diamondNum==DIAMOND_NUM_2){
        diamond->setTexture("shop/diamond_icon_1.png");
    }else{
        diamond->setTexture("shop/diamond_icon_3.png");
        
    }
    diamond->setPosition(0,25);
    this->addChild(diamond);
   
    auto piao = Sprite::create();
    piao->setPosition(0,-65);
    addChild(piao);
    if(diamondNum==DIAMOND_NUM_1){
        piao->setTexture("shop/purple_piaodai.png");
    }else if(diamondNum==DIAMOND_NUM_2){
        piao->setTexture("shop/red_piaodai.png");
    }else{
        piao->setTexture("shop/yellow_piaodai.png");
    }

    LabelAtlas* diamondNumAtl = LabelAtlas::create(StringUtils::format("%d",diamondNum),"shop/prop_num.png",21,28,'0');
    diamondNumAtl->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(diamondNumAtl);
    auto zhuan = Sprite::create("shop/font_diamond.png");
    zhuan->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    addChild(zhuan);
    
    int width = diamondNumAtl->getContentSize().width + zhuan->getContentSize().width;
    diamondNumAtl->setPosition(-width/2,-55);
    zhuan->setPosition(width/2,-55);
    
    auto btnImage = MenuItemImage::create("shop/button_bg_1.png","shop/button_bg_2.png",CC_CALLBACK_1(DiamondItem::confirmCharge, this));
    if(diamondNum==DIAMOND_NUM_1){
        btnImage->setTag(2);
    }else if(diamondNum==DIAMOND_NUM_2){
        btnImage->setTag(3);
    }else{
        btnImage->setTag(4);
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
    
    return true;
}

void DiamondItem::confirmCharge(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*) ref;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->requestEvent(UserData::getInstance()->getPoxiaoId(),StringUtils::format("%d",temp->getTag()));//从2开始
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOSBridge::getInstance()->doPayEvent(UserData::getInstance()->getPoxiaoId(),temp->getTag());
#endif
}