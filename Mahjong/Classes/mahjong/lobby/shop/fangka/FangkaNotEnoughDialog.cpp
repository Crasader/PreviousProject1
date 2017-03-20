//
//  ChargeFangka.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/26.
//
//

#include "mahjong/lobby/shop/fangka/FangkaNotEnoughDialog.hpp"
#include "payment/android/CallAndroidMethod.h"
#include "payment/ios/IOSBridge.h"
#include "server/NetworkManage.h"



bool FangkaNotEnoughDialog::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto dialog_bg = Sprite::create("shop/gold_not_enough.png");
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    
    auto roomTitle = Sprite::create("shop/buy_fangka.png");
    roomTitle->setPosition(640,570);
    addChild(roomTitle);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FangkaNotEnoughDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(910, 525);
    addChild(closeMenu);
    
    
    auto bg_2 = Sprite::create("shop/first_charge_bg_2.png");
    bg_2->setPosition(645,375);
    addChild(bg_2);
    
    
    auto chargeImage = Sprite::create("shop/charge/fangka_buzhu.png");
    chargeImage->setPosition(640,380);
    addChild(chargeImage);
    
    auto fangka = Sprite::create("mjitem/fangka_icon.png");
    fangka->setPosition(540,320);
    addChild(fangka);
    
    auto fangkanum = LabelAtlas::create(StringUtils::format(":%d",1),"shop/charge/charge_num.png",21,30,'0');
    fangkanum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    fangkanum->setPosition(600,325);
    addChild(fangkanum);
    
    auto xuyaunnum = LabelAtlas::create(StringUtils::format("%d",6),"shop/charge/charge_num.png",21,30,'0');
    xuyaunnum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    xuyaunnum->setScale(0.8f);
    xuyaunnum->setPosition(690,320);
    addChild(xuyaunnum);
    
    auto xuyuan = Sprite::create("shop/charge/xu_yuan.png");
    xuyuan->setPosition(680,320);
    addChild(xuyuan);
    
    auto image = MenuItemImage::create("shop/charge_btn_1.png","shop/charge_btn_2.png",
                                       CC_CALLBACK_0(FangkaNotEnoughDialog::confirmCharge, this));
    Menu* menu = Menu::create(image,NULL);
    menu->setPosition(640,210);
    addChild(menu);

    return true;
}

void FangkaNotEnoughDialog::closeView(){
    removeFromParent();
}


void FangkaNotEnoughDialog::confirmCharge(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->requestEvent(UserData::getInstance()->getPoxiaoId(),"7");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOSBridge::getInstance()->doPayEvent(UserData::getInstance()->getPoxiaoId(),7);
#endif
}
