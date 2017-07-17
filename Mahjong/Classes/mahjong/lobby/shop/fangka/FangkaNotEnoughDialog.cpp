//
//  ChargeFangka.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/26.
//
//

#include "mahjong/lobby/shop/fangka/FangkaNotEnoughDialog.hpp"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"
#include "server/NetworkManage.h"



bool FangkaNotEnoughDialog::init(){
    if(!Layer::init()){
        return false;
    }
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 204), 1280, 720);
    addChild(bg0);
    
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto dialog_bg = Sprite::create("shop/first_chage_bg.png");
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    auto roomTitle = Sprite::create("shop/charge/get_fangka_title.png");
    roomTitle->setPosition(640,580);
    addChild(roomTitle);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FangkaNotEnoughDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1000, 595);
    addChild(closeMenu);
    
    
    auto bg_2 = Sprite::create("shop/first_charge_bg_2.png");
    bg_2->setPosition(645,375);
    addChild(bg_2);
    
    
    auto chargeImage = Sprite::create("shop/charge/fangkabuzu1.png");
    chargeImage->setPosition(640,380);
    addChild(chargeImage);
    
    auto fangka = Sprite::create("common/fangka_icon.png");
    fangka->setPosition(540,310);
    addChild(fangka);
    
    fangkanum0 = LabelAtlas::create(StringUtils::format("%d",1),"shop/charge/charge_num.png",24,36,'0');
    fangkanum0->setAnchorPoint(Point::ANCHOR_MIDDLE);
    fangkanum0->setPosition(575,380);
    addChild(fangkanum0);
    
    
    fangkanum = LabelAtlas::create(StringUtils::format(":%d",1),"shop/charge/charge_num.png",24,36,'0');
    fangkanum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    fangkanum->setPosition(600,315);
    addChild(fangkanum);
    
    xuyaunnum = LabelAtlas::create(StringUtils::format("%d",6),"shop/charge/charge_num.png",24,36,'0');
    xuyaunnum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    xuyaunnum->setScale(0.8f);
    xuyaunnum->setPosition(712,310);
    addChild(xuyaunnum);
    
    auto image = MenuItemImage::create("shop/charge_btn_1.png","shop/charge_btn_2.png",
                                       CC_CALLBACK_0(FangkaNotEnoughDialog::confirmCharge, this));
    Menu* menu = Menu::create(image,NULL);
    menu->setPosition(640,150);
    addChild(menu);

    return true;
}

void FangkaNotEnoughDialog::initView(int num,int fee){
    fangkanum->setString(StringUtils::format(":%d",4));
    xuyaunnum->setString(StringUtils::format("%d",6));
}

void FangkaNotEnoughDialog::closeView(){
    removeFromParent();
}


void FangkaNotEnoughDialog::confirmCharge(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->requestEvent(UserData::getInstance()->getPoxiaoId(),"7");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->doPayEvent(UserData::getInstance()->getPoxiaoId(),7);
#endif
}
