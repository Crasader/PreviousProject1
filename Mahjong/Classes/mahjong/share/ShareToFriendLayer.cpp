//
//  WanJiaQunLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/9.
//
//

#include "mahjong/share/ShareToFriendLayer.hpp"
#include "mahjong/utils/GameConfig.h"
#include "mahjong/state/GameData.h"
#include "payment/android/CallAndroidMethod.h"
#import "payment/ios/IOSBridge.h"

bool ShareToFriendLayer::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto  dialogBg = Sprite::create("shop/shop_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ShareToFriendLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1050, 615);
    addChild(closeMenu);
    
    auto titleIcon = Sprite::create("share/share_to_friend_title.png");
    titleIcon->setPosition(640, 660);
    addChild(titleIcon);
    
    auto tabbg = Sprite::create("share/ye_qian_bg.png");
    tabbg->setPosition(420,560);
    addChild(tabbg);
    
    auto qun_normal = MenuItemImage::create("share/ye_qian_btn_1.png", "share/ye_qian_btn_1.png");
    auto qun_selected = MenuItemImage::create("share/ye_qian_btn_2.png", "share/ye_qian_btn_2.png");
    qunToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ShareToFriendLayer::showWanJiaQun, this), qun_normal, qun_selected, NULL);
    
    auto fangka_normal = MenuItemImage::create("share/ye_qian_btn_1.png", "share/ye_qian_btn_1.png");
    auto fangka_selected = MenuItemImage::create("share/ye_qian_btn_2.png", "share/ye_qian_btn_2.png");
    fangkaToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ShareToFriendLayer::showFangkaDai, this), fangka_normal, fangka_selected, NULL);
    
    auto menu = Menu::create(qunToggle, fangkaToggle, NULL);
    menu->alignItemsHorizontallyWithPadding(0);
    menu->setPosition(420,560);
    addChild(menu,1);
    
    fenxiang =  Sprite::create("share/fen_xiang_text_1.png");
    fenxiang->setPosition(310, 560);
    addChild(fenxiang,2);
    
    lingqu =  Sprite::create("share/ke_lin_qu_text_1.png");
    lingqu->setPosition(520, 560);
    addChild(lingqu,2);
    
    qunToggle->setSelectedIndex(0);
    fangkaToggle->setSelectedIndex(1);
    
    //3个展示框
    auto box1 = Sprite::create("share/share_box_bg.png");
    box1->setPosition(Point(360,360));
    addChild(box1);
    
    auto boxTitle1 = Sprite::create("share/box_title_1.png");
    boxTitle1->setPosition(Point(360,480));
    addChild(boxTitle1);
    
    auto boxText1 = Sprite::create("share/box_text_1.png");
    boxText1->setPosition(Point(360,435));
    addChild(boxText1);
    
    auto boxImage1 = Sprite::create("share/box_image_1.png");
    boxImage1->setPosition(Point(360,330));
    addChild(boxImage1);
    
    auto box2 = Sprite::create("share/share_box_bg.png");
    box2->setPosition(Point(640,360));
    addChild(box2);
    
    auto boxTitle2 = Sprite::create("share/box_title_2.png");
    boxTitle2->setPosition(Point(640,480));
    addChild(boxTitle2);
    
    auto boxText2 = Sprite::create("share/box_text_2.png");
    boxText2->setPosition(Point(640,435));
    addChild(boxText2);
    
    auto boxImage2 = Sprite::create("share/box_image_2.png");
    boxImage2->setPosition(Point(640,330));
    addChild(boxImage2);
    
    auto box3 = Sprite::create("share/share_box_bg.png");
    box3->setPosition(Point(920,360));
    addChild(box3);
    
    auto boxTitle3 = Sprite::create("share/box_title_3.png");
    boxTitle3->setPosition(Point(920,480));
    addChild(boxTitle3);
    
    auto boxText3 = Sprite::create("share/box_text_3.png");
    boxText3->setPosition(Point(920,435));
    addChild(boxText3);
    
    auto boxImage3 = Sprite::create("share/box_image_3.png");
    boxImage3->setPosition(Point(920,330));
    addChild(boxImage3);
    
    auto boxText4 = Sprite::create("share/box_text_huode.png");
    boxText4->setPosition(Point(920,250));
    addChild(boxText4);
    
    auto shareText = Sprite::create("share/share_text.png");
    shareText->setPosition(Point(640,190));
    addChild(shareText);
    
    auto shareImage = MenuItemImage::create("share/share_btn_1.png","share/share_btn_2.png",
                                           CC_CALLBACK_0(ShareToFriendLayer::doFaHongBaoPerson, this));
    auto friendImage = MenuItemImage::create("share/friend_btn_1.png","share/friend_btn_2.png",
                                           CC_CALLBACK_0(ShareToFriendLayer::doFaHongBaoFriend, this));
    
    Menu* myMneu = Menu::create(shareImage,friendImage,NULL);
    myMneu->setPosition(640,125);
    myMneu->alignItemsHorizontallyWithPadding(50);
    addChild(myMneu);
    
    return true;
}


void ShareToFriendLayer::closeView(){
    removeFromParent();
}

void ShareToFriendLayer::showWanJiaQun(Ref* ref){
    qunToggle->setSelectedIndex(0);
    fangkaToggle->setSelectedIndex(1);
    fenxiang->setTexture("share/fen_xiang_text_1.png");
    lingqu->setTexture("share/ke_lin_qu_text_2.png");
}


void ShareToFriendLayer::showFangkaDai(Ref* ref){
    qunToggle->setSelectedIndex(1);
    fangkaToggle->setSelectedIndex(0);
    fenxiang->setTexture("share/fen_xiang_text_2.png");
    lingqu->setTexture("share/ke_lin_qu_text_1.png");
}

void ShareToFriendLayer::doFaHongBaoPerson(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    CallAndroidMethod::getInstance()->shareToWeChat(url,SHARE_TEXT_1, SHARE_TEXT_2,false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    IOSBridge::getInstance()->doWechatShareWeb(url,SHARE_TEXT_1, SHARE_TEXT_2,0);
#endif
}

void ShareToFriendLayer:: doFaHongBaoFriend(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    CallAndroidMethod::getInstance()->shareToWeChat(url,SHARE_TEXT_1, SHARE_TEXT_2,true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    IOSBridge::getInstance()->doWechatShareWeb(url, SHARE_TEXT_1, SHARE_TEXT_2,1);
#endif
}
