//
//  ChargeDiamond.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/18.
//
//

#include "game/mahjong/shop/ChargeDiamond.hpp"
#include "game/mahjong/shop/ShopHintDialog.hpp"
#include "game/mahjong/state/GameData.h"
#include "game/loading/Loading.h"
#include "server/NetworkManage.h"
#include "game/utils/StringUtil.h"
#include "payment/android/CallAndroidMethod.h"


bool ChargeDiamond::init(){

    if(!Layer::init()){
    
        return false;
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDiamondChangeListCommand());
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto dialog_bg = Sprite::create("shop/charge_bg.png");
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/charge_title.png");
    title->setPosition(654,560);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ChargeDiamond::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1050, 550);
    addChild(closeMenu);
    
    if(!GAMEDATA::getInstance()->getDiamondChangeList().needInit){
        Loading* lod = Loading::create(true);
        lod->setTag(1000);
        addChild(lod);
    }else{
        showChargeDialog();
    }

    return true;

}


void ChargeDiamond::onEnter(){
    Layer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_GOLD_CHANGE_LIST, [=](EventCustom* event){
        if(NULL != getChildByTag(1000)){
            getChildByTag(1000)->removeFromParent();
        }
        showChargeDialog();
    });
}

void ChargeDiamond::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(MSG_PLAYER_GOLD_CHANGE_LIST);
}

void ChargeDiamond::showChargeDialog(){
     DiamondChangeList list = GAMEDATA::getInstance()->getDiamondChangeList();
    for(int i=0;i<list.list.size();i++){
        auto propBg =  Sprite::create("shop/prop_bg.png");
        propBg->setPosition(285+175*i,345);
        addChild(propBg);
        
        auto light = Sprite::create("shop/diamond_bg.png");
        light->setPosition(285+175*i,370);
        addChild(light);
        
        auto diamond = Sprite::create();
        if(i==0){
            diamond->setTexture("shop/diamond_icon_2.png");
        }else if(i==1||i==2){
            diamond->setTexture("shop/diamond_icon_1.png");
        }else{
            diamond->setTexture("shop/diamond_icon_3.png");

        }
        diamond->setPosition(285+175*i,370);
        this->addChild(diamond);
        
        auto piao = Sprite::create();
        piao->setPosition(285+175*i,280);
        addChild(piao);
        if(i==0){
            piao->setTexture("shop/purple_piaodai.png");
        }else if(i==1||i==2){
            piao->setTexture("shop/red_piaodai.png");
        }else{
            piao->setTexture("shop/yellow_piaodai.png");
            
        }
        
        LabelAtlas* diamondNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d",list.list.at(i).diamond)->_string,"shop/prop_num.png",21,28,'0');
        diamondNum->setPosition(290+175*i,291);
        diamondNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        addChild(diamondNum);
        
        auto zhuan = Sprite::create("shop/font_diamond.png");
        zhuan->setPosition(320+175*i,291);
        addChild(zhuan);
        
        
        auto btnImage = MenuItemImage::create("shop/button_bg_1.png","shop/button_bg_2.png",CC_CALLBACK_1(ChargeDiamond::chargeButtonClick, this));
        auto myMenu = Menu::create(btnImage,NULL);
        myMenu->setPosition(285+175*i,225);
        addChild(myMenu);
        
        LabelAtlas* money = LabelAtlas::create(cocos2d::String::createWithFormat("%d",list.list.at(i).money/100)->_string,"shop/prop_num.png",21,28,'0');
        money->setPosition(300+175*i,230);
        money->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        addChild(money);
        
        auto yuan = Sprite::create("shop/font_yuan.png");
        yuan->setPosition(325+175*i,225);
        addChild(yuan);

        
    }

}

void ChargeDiamond::closeView(){
    removeFromParent();

}

void ChargeDiamond::chargeButtonClick(Ref* ref){
    CallAndroidMethod::getInstance()->requestEvent(UserData::getInstance()->getPoxiaoId(),"1");
}