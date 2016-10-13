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


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "payment/ios/IOSBridge.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "payment/android/CallAndroidMethod.h"
#endif

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
    
//    
//    auto kouling = Sprite::create("shop/hongbaokoulin.png");
//    kouling->setPosition(570,520);
//    addChild(kouling);
//    
//    auto koulingText = Label::create(cocos2d::String::createWithFormat("%s",GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str())->_string,"arial",30);
//    koulingText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    koulingText->setColor(Color3B::YELLOW);
//    koulingText->setPosition(670,520);
//    addChild(koulingText);
    
    auto hongbaoBg1 = Sprite::create("shop/red_box.png");
    hongbaoBg1->setPosition(480,320);
    hongbaoBg1->setScaleY(0.7);
    addChild(hongbaoBg1);
    
    auto piaodai1 = Sprite::create("shop/lvse_piaodai.png");
    piaodai1->setPosition(480,450);
    addChild(piaodai1);
    
    auto title1 = Sprite::create("shop/wxhy_text.png");
    title1->setPosition(480,470);
    addChild(title1);
    
    auto wxIcon1 = Sprite::create("shop/wx_icon.png");
    wxIcon1->setPosition(480,350);
    addChild(wxIcon1);
    
    auto btnImage = MenuItemImage::create("shop/fahongbao_btn_1.png","shop/fahongbao_btn_2.png",CC_CALLBACK_0(HongbaoPride::doFaHongBaoPerson, this));
    auto menu1= Menu::create(btnImage,NULL);
    menu1->setPosition(480,210);
    addChild(menu1);
    
    auto hongbaoBg2 = Sprite::create("shop/red_box.png");
    hongbaoBg2->setPosition(810,320);
    hongbaoBg2->setScaleY(0.7);
    addChild(hongbaoBg2);
    
    auto piaodai2 = Sprite::create("shop/lvse_piaodai.png");
    piaodai2->setPosition(810,450);
    addChild(piaodai2);
    
    auto title2 = Sprite::create("shop/pyq_text.png");
    title2->setPosition(810,470);
    addChild(title2);
    
    auto wxIcon2 = Sprite::create("shop/pyq_icon.png");
    wxIcon2->setPosition(810,350);
    addChild(wxIcon2);
    
    auto btnImage2 = MenuItemImage::create("shop/fahongbao_btn_1.png","shop/fahongbao_btn_2.png",CC_CALLBACK_0(HongbaoPride::doFaHongBaoFriend, this));
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
    CallAndroidMethod::getInstance()->shareToWeChat(url,"来来来！敲麻发红包了", "20花敲麻，帮好朋友一道开房间搓麻将，点我领红包",false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    IOSBridge::getInstance()->doWechatShareWeb(url,"来来来！敲麻发红包了", "20花敲麻，帮好朋友一道开房间搓麻将，点我领红包");
#endif
}

void HongbaoPride:: doFaHongBaoFriend(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
     std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    CallAndroidMethod::getInstance()->shareToWeChat(url,"来来来！敲麻发红包了", "20花敲麻，帮好朋友一道开房间搓麻将，点我领红包",true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    IOSBridge::getInstance()->doWechatShareWeb(url, "来来来！敲麻发红包了", "20花敲麻，帮好朋友一道开房间搓麻将，点我领红包");
#endif
}
