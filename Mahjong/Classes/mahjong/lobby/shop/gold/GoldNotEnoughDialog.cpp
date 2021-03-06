//
//  GoldNotEnoughDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/12.
//
//

#include "mahjong/lobby/shop/gold/GoldNotEnoughDialog.hpp"
#include "mahjong/lobby/shop/gold/ChargeGold.hpp"
#include "mahjong/lobby/goldroom/GoldRoomButton.hpp"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/GameConfig.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"

GoldNotEnoughDialog* GoldNotEnoughDialog::create(EnterRoomResp newRespData){
    GoldNotEnoughDialog* ret = new GoldNotEnoughDialog();
    if(ret &&ret->init(newRespData)){
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool GoldNotEnoughDialog::init(EnterRoomResp newRespData){
    if(!Layer::init()){
        return false;
    }
    
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 204), 1280, 720);
    addChild(bg0);
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu0 = Menu::create(item1, NULL);
    this->addChild(menu0);
    
    auto dialogBg = Sprite::create("shop/first_chage_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(GoldNotEnoughDialog::closeView, this));
    auto closeMenu = Menu::create(close, NULL);
    closeMenu->setPosition(1000, 590);
    this->addChild(closeMenu);
    
    auto title = Sprite::create("shop/charge/get_gold_title.png");
    title->setPosition(640, 590);
    this->addChild(title);
    
    auto jinbiContent = Sprite::create("shop/charge/jinbibuzu.png");
    jinbiContent->setPosition(640,400);
    addChild(jinbiContent);
    
    int goldShowNum =atoi(newRespData.min.c_str());
    
    
    auto fangkanum0 = LabelAtlas::create(StringUtils::format("%d",goldShowNum/10000),"shop/charge/charge_num.png",24,36,'0');
    fangkanum0->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fangkanum0->setPosition(525,400);
    addChild(fangkanum0);
    
    auto wan = Sprite::create("shop/charge/text_wan.png");
    wan->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    wan->setPosition(fangkanum0->getPositionX()+fangkanum0->getContentSize().width,395);
    addChild(wan);
    
    auto fangkanum = LabelAtlas::create(StringUtils::format(":%d",goldShowNum),"shop/charge/charge_num.png",24,36,'0');
    fangkanum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    fangkanum->setPosition(655,332);
    addChild(fangkanum);
    
    auto fangka = Sprite::create("common/gold_icon.png");
    fangka->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    fangka->setPosition(fangkanum->getPositionX()-fangkanum->getContentSize().width,330);
    addChild(fangka);
    
    auto xuyaunnum = LabelAtlas::create(StringUtils::format("%d",5),"shop/charge/charge_num.png",24,36,'0');
    xuyaunnum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    xuyaunnum->setScale(0.8f);
    xuyaunnum->setPosition(742,330);
    addChild(xuyaunnum);

    auto confirm = MenuItemImage::create("shop/charge/charge_btn_1.png", "shop/charge/charge_btn_2.png",
                                         CC_CALLBACK_0(GoldNotEnoughDialog::chargeGold, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 160);
    addChild(confirmMenu);
    
    if(UserData::getInstance()->getUserPayWay() == "2"){
        fangkanum->setString(StringUtils::format(":%s",GAMEDATA::getInstance()->getPayGoldPoint().applegold.c_str()));
        xuyaunnum->setString(StringUtils::format("%s",GAMEDATA::getInstance()->getPayGoldPoint().applefee.c_str()));
    }else{
        fangkanum->setString(StringUtils::format(":%s",GAMEDATA::getInstance()->getPayGoldPoint().gold.c_str()));
        xuyaunnum->setString(StringUtils::format("%s",GAMEDATA::getInstance()->getPayGoldPoint().fee.c_str()));
    }

    
    return true;
}

void GoldNotEnoughDialog::closeView(){
    removeFromParent();
}


void GoldNotEnoughDialog::chargeGold(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->requestEvent(UserData::getInstance()->getPoxiaoId(), GAMEDATA::getInstance()->getPayGoldPoint().payId);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->doPayEvent(UserData::getInstance()->getPoxiaoId(),atoi(GAMEDATA::getInstance()->getPayGoldPoint().payId.c_str()));
#endif
}
