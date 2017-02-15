//
//  WanJiaQunLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/9.
//
//

#include "mahjong/share/ShareToFriendLayer.hpp"
#include "mahjong/utils/GameConfig.h"
#include "http/image/UrlImageMannger.h"

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

