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
#include "http/image/UrlImageMannger.h"

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
    
    std::string temp0 = UserData::getInstance()->getJiZanText();
    int pos  = (int)temp0.find(UserData::getInstance()->getJiZanKefu());
    std::string temp1 = temp0.substr(0,pos);
    std::string temp3 = temp0.substr(pos+UserData::getInstance()->getJiZanKefu().size(),temp0.size());
    
    auto textlabel2 = Label::createWithSystemFont(UserData::getInstance()->getJiZanKefu(),"arial",24);
    textlabel2->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    textlabel2->setPosition(840,500);
    textlabel2->setColor(Color3B(67,128,238));
    addChild(textlabel2);
    
    auto textlabel = Label::createWithSystemFont(temp1,"arial",24);
    textlabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    textlabel->setPosition(textlabel2->getPositionX()-textlabel2->getContentSize().width,500);
    textlabel->setColor(Color3B(196,106,22));
    addChild(textlabel);
    auto textlabel3 = Label::createWithSystemFont(temp3,"arial",24);
    textlabel3->setAlignment(cocos2d::TextHAlignment::CENTER);
    textlabel3->setPosition(640,470);
    textlabel3->setColor(Color3B(196,106,22));
    addChild(textlabel3);
    auto copyImage = MenuItemImage::create("share/btn_share_copy_1.png","share/btn_share_copy_2.png",CC_CALLBACK_0(ShareSelectLayer::copyText, this));
    copyImage->setScale(0.7f);
    auto copyMenu = Menu::create(copyImage,NULL);
    copyMenu->alignItemsHorizontallyWithPadding(50);
    copyMenu->setPosition(920,500);
    addChild(copyMenu);
    
    auto quanMenu = MenuItemImage::create("share/share_quan.png","share/share_quan.png",CC_CALLBACK_0(ShareSelectLayer::shareToQuan, this));
    auto friendMenu = MenuItemImage::create("share/share_friend.png","share/share_friend.png",CC_CALLBACK_0(ShareSelectLayer::shareToFriend, this));
    
    auto menu = Menu::create(quanMenu,friendMenu,NULL);
    menu->alignItemsHorizontallyWithPadding(50);
    menu->setPosition(640,310);
    addChild(menu);
    return true;
}


void ShareSelectLayer::shareToQuan(){
    std::string shareUrl = GAMEDATA::getInstance()->getMahjongShareData4().url;
    if(GAMEDATA::getInstance()->getMahjongShareData4().type == "1"){
        shareUrl = StringUtils::format("%s%s",shareUrl.c_str(),UserData::getInstance()->getPoxiaoId().c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CallAndroidMethod::getInstance()->shareToWeChat(shareUrl,GAMEDATA::getInstance()->getMahjongShareData4().head,GAMEDATA::getInstance()->getMahjongShareData4().content,true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CallIOSMethod::getInstance()->doWechatShareWeb(shareUrl,GAMEDATA::getInstance()->getMahjongShareData4().head,GAMEDATA::getInstance()->getMahjongShareData4().content,1);
#endif
    }else{
        UrlImageMannger::getInstance()->downloadShareImageByUrl(GAMEDATA::getInstance()->getMahjongShareData4().pic,true);
    }
}

void ShareSelectLayer::shareToFriend(){
    std::string shareUrl = GAMEDATA::getInstance()->getMahjongShareData4().url;
    if(GAMEDATA::getInstance()->getMahjongShareData4().type == "1"){
        shareUrl = StringUtils::format("%s%s",shareUrl.c_str(),UserData::getInstance()->getPoxiaoId().c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CallAndroidMethod::getInstance()->shareToWeChat(shareUrl,GAMEDATA::getInstance()->getMahjongShareData4().phead,GAMEDATA::getInstance()->getMahjongShareData4().pcontent,false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CallIOSMethod::getInstance()->doWechatShareWeb(shareUrl,GAMEDATA::getInstance()->getMahjongShareData4().phead,GAMEDATA::getInstance()->getMahjongShareData4().pcontent,0);
#endif
    }else{
        UrlImageMannger::getInstance()->downloadShareImageByUrl(GAMEDATA::getInstance()->getMahjongShareData4().pic,false);
    }
}

void ShareSelectLayer::copyText(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->copyToPasteboard(UserData::getInstance()->getJiZanKefu());
#endif
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->copyToPasteboard(UserData::getInstance()->getJiZanKefu());
#endif
    toast();
}

void ShareSelectLayer::toast(){
    auto bg = Sprite::create("common/toast_bg.png");
    bg->setAnchorPoint(Point::ANCHOR_MIDDLE);
    bg->setPosition(650,300);
    bg->setScaleX(0.2);
    addChild(bg);
    auto shui = Label::createWithSystemFont("复制成功","arial",26);
    shui->setColor(Color3B(255,183,64));
    shui->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    shui->setPosition(600,300);
    addChild(shui);
    
    bg->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){
        bg->setVisible(false);
    }), NULL));
    shui->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){
        shui->setVisible(false);
    }), NULL));
}


void ShareSelectLayer::closeView(){
    removeFromParent();
}
