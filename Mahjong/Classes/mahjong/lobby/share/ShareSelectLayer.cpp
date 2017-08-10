//
//  ShareSelectlayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/9.
//
//

#include "mahjong/lobby/share/ShareSelectLayer.hpp"
#include "mahjong/common/state/GameData.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"

bool ShareSelectLayer::init(){
    
    if(!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ShareSelectLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(990, 595);
    addChild(closeMenu);
    
    auto titile = Sprite::create("share/title_fenxiangjizan.png");
    titile->setPosition(645,582);
    addChild(titile);
    
    auto textlabel = Label::createWithSystemFont(UserData::getInstance()->getShareTextContent(),"arial",24);
    textlabel->setWidth(700);
    textlabel->setAlignment(cocos2d::TextHAlignment::CENTER);
    textlabel->setPosition(640,500);
    textlabel->setColor(Color3B(196,106,22));
    addChild(textlabel);
    
    auto quanMenu = MenuItemImage::create("share/share_quan.png","share/share_quan.png",CC_CALLBACK_0(ShareSelectLayer::shareToQuan, this));
    auto friendMenu = MenuItemImage::create("share/share_friend.png","share/share_friend.png",CC_CALLBACK_0(ShareSelectLayer::shareToFriend, this));
    
    auto menu = Menu::create(quanMenu,friendMenu,NULL);
    menu->alignItemsHorizontallyWithPadding(50);
    menu->setPosition(640,320);
    addChild(menu);
    return true;
}


void ShareSelectLayer::shareToQuan(){
    std::string shareUrl = GAMEDATA::getInstance()->getMahjongShareData1().url;
    if(GAMEDATA::getInstance()->getMahjongShareData1().type == "1"){
        shareUrl = StringUtils::format("%s%s",shareUrl.c_str(),UserData::getInstance()->getPoxiaoId().c_str());
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->shareToWeChat(shareUrl,GAMEDATA::getInstance()->getMahjongShareData1().head,GAMEDATA::getInstance()->getMahjongShareData1().content,true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->doWechatShareWeb(shareUrl,GAMEDATA::getInstance()->getMahjongShareData1().head,GAMEDATA::getInstance()->getMahjongShareData1().content,1);
#endif
}

void ShareSelectLayer::shareToFriend(){
    std::string shareUrl = GAMEDATA::getInstance()->getMahjongShareData1().url;
    if(GAMEDATA::getInstance()->getMahjongShareData1().type == "1"){
        shareUrl = StringUtils::format("%s%s",shareUrl.c_str(),UserData::getInstance()->getPoxiaoId().c_str());
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->shareToWeChat(shareUrl,GAMEDATA::getInstance()->getMahjongShareData1().phead,GAMEDATA::getInstance()->getMahjongShareData1().pcontent,false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->doWechatShareWeb(shareUrl,GAMEDATA::getInstance()->getMahjongShareData1().phead,GAMEDATA::getInstance()->getMahjongShareData1().pcontent,0);
#endif
}

void ShareSelectLayer::closeView(){
    removeFromParent();
}
