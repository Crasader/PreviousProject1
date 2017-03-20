//
//  DiamondItem.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/13.
//
//

#include "mahjong/shop/fangka/ChargeItem.hpp"
#include "payment/android/CallAndroidMethod.h"
#include "payment/ios/IOSBridge.h"

#define FANGKA_NUM 5

ChargeItem* ChargeItem::create(int price,int fangakNum,int payId){
    
    ChargeItem* ret = new ChargeItem();
    if(ret &&ret->init(price,fangakNum,payId)){
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool ChargeItem::init(int price, int fangakNum,int payId){
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
    
    
    LabelAtlas* fangkaNum = LabelAtlas::create(StringUtils::format("%d",fangakNum),"result/fan_num.png",17,26,'0');
    fangkaNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    fangkaNum->setPosition(-32,-52);
    addChild(fangkaNum,2);
    auto fangkatext = Sprite::create();
    fangkatext->setTexture("shop/fangka_num_text.png");
    fangkatext->setPosition(22,-52);
    this->addChild(fangkatext,2);
    
    auto piao = Sprite::create();
    piao->setPosition(0,-65);
    addChild(piao);
     piao->setTexture("shop/purple_piaodai.png");
    if(fangakNum>=FANGKA_NUM){
        piao->setTexture("shop/red_piaodai.png");
    }
    
    auto btnImage = MenuItemImage::create("shop/button_bg_1.png","shop/button_bg_2.png",CC_CALLBACK_1(ChargeItem::confirmCharge, this));
    btnImage->setTag(payId);
    auto myMenu = Menu::create(btnImage,NULL);
    myMenu->setPosition(0,-118);
    addChild(myMenu);
    
    LabelAtlas* money = LabelAtlas::create(StringUtils::format("%d",price/100),"shop/charge_btn_num.png",26,32,'0');
    money->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(money);
    
    auto yuan = Sprite::create("shop/font_yuan.png");
    yuan->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    addChild(yuan);
    
    int width2 = money->getContentSize().width + yuan->getContentSize().width;
    money->setPosition(-width2/2,-115);
    yuan->setPosition(width2/2,-115);
    
    if(fangakNum>FANGKA_NUM){
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
