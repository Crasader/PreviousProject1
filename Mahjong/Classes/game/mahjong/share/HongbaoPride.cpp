//
//  HongbaoPride.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/21.
//
//

#include "game/mahjong/share/HongbaoPride.hpp"
#include "game/mahjong/state/GameData.h"
#include "game/utils/GameConfig.h"
#include "payment/android/CallAndroidMethod.h"
#import "payment/ios/IOSBridge.h"


bool HongbaoPride::init(){
    if(!Layer::init()){
        
        return false;
    }
    
    showHongbaoPride();
    return true;
    
}

void HongbaoPride::showHongbaoPride(){
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu0 = Menu::create(item1, NULL);
    this->addChild(menu0);
    
    
    auto  dialogBg = Sprite::create("shop/shop_bg_2.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(HongbaoPride::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 580);
    addChild(closeMenu);
    
    auto title = Sprite::create("shop/haoyoufahongbao.png");
    title->setPosition(640,610);
    addChild(title);
    
    
    auto hongbaoBg1 = Sprite::create("shop/red_box.png");
    hongbaoBg1->setPosition(480,320);
    hongbaoBg1->setScaleY(0.7);
    addChild(hongbaoBg1);

    
    auto wxIcon1 = Sprite::create("shop/wx_icon.png");
    wxIcon1->setPosition(480,360);
    addChild(wxIcon1);
    
    auto btnImage = MenuItemImage::create("shop/send_to_friend_1.png","shop/send_to_friend_2.png",CC_CALLBACK_0(HongbaoPride::doFaHongBaoPerson, this));
    auto menu1= Menu::create(btnImage,NULL);
    menu1->setPosition(480,210);
    addChild(menu1);
    
    auto hongbaoBg2 = Sprite::create("shop/red_box.png");
    hongbaoBg2->setPosition(810,320);
    hongbaoBg2->setScaleY(0.7);
    addChild(hongbaoBg2);
    
    
    auto wxIcon2 = Sprite::create("shop/pyq_icon.png");
    wxIcon2->setPosition(810,360);
    addChild(wxIcon2);
    
    auto btnImage2 = MenuItemImage::create("shop/send_to_quan_1.png","shop/send_to_quan_2.png",CC_CALLBACK_0(HongbaoPride::doFaHongBaoFriend, this));
    auto menu2= Menu::create(btnImage2,NULL);
    menu2->setPosition(810,210);
    addChild(menu2);
}


void  HongbaoPride::closeView(){
    removeFromParent();
}

void HongbaoPride::doFaHongBaoPerson(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    CallAndroidMethod::getInstance()->shareToWeChat(url,SHARE_TEXT_1, SHARE_TEXT_2,false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    IOSBridge::getInstance()->doWechatShareWeb(url,SHARE_TEXT_1, SHARE_TEXT_2,0);
#endif
}

void HongbaoPride:: doFaHongBaoFriend(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
     std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    CallAndroidMethod::getInstance()->shareToWeChat(url,SHARE_TEXT_1, SHARE_TEXT_2,true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    IOSBridge::getInstance()->doWechatShareWeb(url, SHARE_TEXT_1, SHARE_TEXT_2,1);
#endif
}
