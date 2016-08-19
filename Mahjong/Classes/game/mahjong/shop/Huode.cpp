//
//  Huode.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/26.
//
//

#include "game/mahjong/shop/Huode.hpp"

Huode* Huode::create(int gold,int diamond,int lequan){
    Huode* huo = new Huode();
    if(huo && huo->init(gold, diamond, lequan)){
        huo->autorelease();
    }else{
        CC_SAFE_DELETE(huo);
        huo = NULL;
    }
    return huo;

}


bool Huode::init(int goldNum,int diamondNum,int lequanNum){
    if(!Layer::init()){
        return false;
    }
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    addChild(menu1);
    auto all_bg = Sprite::create("common/all_bg.jpg");
    all_bg->setPosition(640, 360);
    addChild(all_bg);
    
    auto diaBg = Sprite::create("shop/shop_bg_4.png");
    diaBg->setAnchorPoint(Point::ANCHOR_MIDDLE);
    diaBg->setPosition(640,360);
    addChild(diaBg);
    
    auto title = Sprite::create("shop/huode.png");
    title->setPosition(290,440);
    diaBg->addChild(title);
    

    auto iamge = MenuItemImage::create("common/confirm_btn_1.png","common/confirm_btn_2.png",CC_CALLBACK_0(Huode::confirm,this));
    auto confirmMenu = Menu::create(iamge,NULL);
    confirmMenu->setPosition(290,80);
    diaBg->addChild(confirmMenu);
    
    if(goldNum!=0){
        auto goldBg = Sprite::create("shop/gold_bg_light.png");
        diaBg->addChild(goldBg);
        
        auto goldIcon = Sprite::create("shop/gold_icon_1.png");
        diaBg->addChild(goldIcon);
        
        auto gNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d",goldNum)->_string,"shop/prop_num.png",21,28,'0');
        gNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
        diaBg->addChild(gNum);
        
        if(lequanNum!=0&&diamondNum!=0){
            goldBg->setPosition(110,250);
            goldIcon->setPosition(110,250);
            gNum->setPosition(110,180);
        }else if((lequanNum==0&&diamondNum!=0)||(lequanNum!=0&&diamondNum==0)){
            goldBg->setPosition(160,250);
            goldIcon->setPosition(160,250);
            gNum->setPosition(160,180);
        }else{
            goldBg->setPosition(290,250);
            goldIcon->setPosition(290,250);
            gNum->setPosition(290,180);
        }
    }
    
    if(lequanNum!=0){
        auto lequanBg = Sprite::create("shop/lequan_light.png");
        diaBg->addChild(lequanBg);
        
        auto leuqnIcon = Sprite::create("shop/lequan_da.png");
        diaBg->addChild(leuqnIcon);
        
        auto lNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d",lequanNum)->_string,"shop/prop_num.png",21,28,'0');
         lNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
        diaBg->addChild(lNum);
        
        if(goldNum!=0&&diamondNum!=0){
            lequanBg->setPosition(290,250);
            leuqnIcon->setPosition(290,250);
            lNum->setPosition(290,180);
        }else if(goldNum==0&&diamondNum!=0){
            lequanBg->setPosition(160,250);
            leuqnIcon->setPosition(160,250);
            lNum->setPosition(160,180);
        }else if(goldNum!=0&&diamondNum==0){
            lequanBg->setPosition(420,250);
            leuqnIcon->setPosition(420,250);
            lNum->setPosition(420,180);
        }
        else{
            lequanBg->setPosition(290,250);
            leuqnIcon->setPosition(290,250);
            lNum->setPosition(290,180);
        }

    }
  
    if(diamondNum!=0){
        auto diamondBG = Sprite::create("shop/diamond_bg.png");
        diaBg->addChild(diamondBG);
        
        auto diamond = Sprite::create("shop/diamond_icon_1.png");
        diaBg->addChild(diamond);
        
        auto dNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d",diamondNum)->_string,"shop/prop_num.png",21,28,'0');
         dNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
        diaBg->addChild(dNum);
        
        if(goldNum!=0&&lequanNum!=0){
            diamondBG->setPosition(470,250);
            diamond->setPosition(470,250);
            dNum->setPosition(470,180);
        }else if((lequanNum==0&&goldNum!=0)||(lequanNum!=0&&goldNum==0)){
            diamondBG->setPosition(420,250);
            diamond->setPosition(420,250);
            dNum->setPosition(420,180);
        }
        else{
            diamondBG->setPosition(290,250);
            diamond->setPosition(290,250);
            dNum->setPosition(290,180);
        }
    
    }
    
    return true;
}


void Huode::confirm(){
    removeFromParent();
}

