//
//  FirstChageDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/18.
//
//

#include "mahjong/lobby/shop/FirstChageDialog.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/loading/Loading.h"
#include "server/NetworkManage.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"

bool FirstChargeDialog::init(){
    
    if(!Layer::init()){
        return false;
    }
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto dialog_bg = Sprite::create("shop/first_chage_bg.png");
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/first_charge_title.png");
    title->setPosition(654,600);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FirstChargeDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1000, 600);
    addChild(closeMenu);
    
    Loading* lod = Loading::create(true);
    lod->setTag(1000);
    addChild(lod);
    
    return true;
}

void FirstChargeDialog::onEnter(){
    Layer::onEnter();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFirstChargeInfoCommand());
    firstChargeInfo = EventListenerCustom::create(MSG_PLAYER_FIRST_CHARGE, [=](EventCustom* event){
        if(NULL != getChildByTag(1000)){
            getChildByTag(1000)->removeFromParent();
        }
        showFirstCharge();
    });
    _eventDispatcher->addEventListenerWithFixedPriority(firstChargeInfo, 1);
}

void FirstChargeDialog::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(firstChargeInfo);
}

void FirstChargeDialog::showFirstCharge(){
    
//    LabelAtlas* firNum = LabelAtlas::create(StringUtils::format("%d",GAMEDATA::getInstance()->getFirstChargeData().money), "shop/first_charge_num.png", 24, 37, '0');
//    firNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
//    firNum->setPosition(605,520);
//    addChild(firNum);
    
    auto tenyuan = Sprite::create("shop/first_charge_10yuan.png");
    tenyuan->setPosition(665,540);
    addChild(tenyuan);
    
    auto bg_2 = Sprite::create("shop/first_charge_bg_2.png");
    bg_2->setPosition(645,390);
    addChild(bg_2);
    
//    auto diamondBG = Sprite::create("shop/gold_bg_light.png");
//    diamondBG->setPosition(400,400);
//    addChild(diamondBG);
    
//    auto diamond = Sprite::create("shop/fangka_image.png");
//    diamond->setPosition(400,400);
//    addChild(diamond);
    
//    LabelAtlas* fangNum = LabelAtlas::create(StringUtils::format("%d",GAMEDATA::getInstance()->getFirstChargeData().fangka), "result/fan_num.png", 17, 26, '0');
//    fangNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
//    fangNum->setPosition(360,325);
//    addChild(fangNum);
    
//    auto zuanshi = Sprite::create("shop/fangka_2.png");
//    zuanshi->setPosition(400,325);
//    addChild(zuanshi);
    
//    auto plus1= Sprite::create("shop/plus.png");
//    plus1->setPosition(510,400);
//    addChild(plus1);
    
//    auto goldBg = Sprite::create("shop/gold_bg_light.png");
//    goldBg->setPosition(645,400);
//    addChild(goldBg);
    
//    auto goldIcon = Sprite::create("shop/gold_icon_1.png");
//    goldIcon->setPosition(645,400);
//    addChild(goldIcon);
    
//    auto goldNum = LabelAtlas::create(StringUtils::format("%d",GAMEDATA::getInstance()->getFirstChargeData().gold),"shop/prop_num.png",21,28,'0');
//    goldNum->setPosition(645,325);
//    goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
//    addChild(goldNum);
    
//    auto jinbi = Sprite::create("shop/gold_text.png");
//    jinbi->setPosition(685,325);
//    addChild(jinbi);
    
//    auto plus2 = Sprite::create("shop/plus.png");
//    plus2->setPosition(740,400);
//    addChild(plus2);
//    
//    auto permission = Sprite::create("shop/permission.png");
//    permission->setPosition(875,400);
//    addChild(permission);
//    
//    auto tuhao = Sprite::create("shop/tuhao_text.png");
//    tuhao->setPosition(875,325);
//    addChild(tuhao);
//    
    auto image = MenuItemImage::create("shop/charge_btn_1.png","shop/charge_btn_2.png",
                                       CC_CALLBACK_0(FirstChargeDialog::charge, this));
    Menu* menu = Menu::create(image,NULL);
    menu->setPosition(640,160);
    addChild(menu);
    
}

void FirstChargeDialog:: closeView(){
    removeFromParent();
}

void FirstChargeDialog:: charge(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->requestEvent(UserData::getInstance()->getPoxiaoId(), "1");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->doPayEvent(UserData::getInstance()->getPoxiaoId(),1);
#endif
    removeFromParent();
}



