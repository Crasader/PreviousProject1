//
//  AgencyLayer.cpp
//  SuZhouMahjong
//
//  Created by qiuzhong on 2017/11/22.
//

#include "mahjong/lobby/agency/AgencyLayer.hpp"
#include "mahjong/lobby/agency/AgencyResult.hpp"
#include "server/NetworkManage.h"

bool AgencyLayer::init(){
    if(!Layer::init()){
        return false;
    }
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 100), 1280, 720);
    addChild(bg0);
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, nullptr);
    addChild(menu1);
    auto dialog_bg = Sprite::create("competition/competition_bg.png");
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(AgencyLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1170, 660);
    addChild(closeMenu);
    
    auto ag_bg = Sprite::create("agency/agency_bg.png");
    ag_bg->setPosition(640,335);
    addChild(ag_bg);
    
    auto titlebg = Sprite::create("agency/tab_bg.png");
    titlebg->setPosition(640,670);
    addChild(titlebg);
    
    auto agencyBtn1 = Sprite::create("agency/tab_btn.png");
    agencyBtn1->setPosition(520,672);
    agencyBtn1->setTag(1115);
    addChild(agencyBtn1);
    
    auto yikai = Sprite::create("agency/yikai_2.png");
    yikai->setPosition(510,670);
    yikai->setTag(1116);
    addChild(yikai);
    
    
    
    auto agencyBtn2 = Sprite::create("agency/tab_btn.png");
    agencyBtn2->setPosition(755,672);
    agencyBtn2->setTag(1117);
    agencyBtn2->setVisible(false);
    addChild(agencyBtn2);
    
    auto jilu = Sprite::create("agency/jilu_1.png");
    jilu->setPosition(740,670);
    jilu->setTag(1118);
    addChild(jilu);
    
    auto menuImage1 = MenuItem::create();
    menuImage1->setContentSize(yikai->getContentSize());
    menuImage1->setCallback(CC_CALLBACK_0(AgencyLayer::showYiKai, this));
    auto daikaimenu = Menu::create(menuImage1,NULL);
    daikaimenu->setPosition(510,670);
    addChild(daikaimenu);
    
    auto menuImage2 = MenuItem::create();
    menuImage2->setContentSize(jilu->getContentSize());
    menuImage2->setCallback(CC_CALLBACK_0(AgencyLayer::showJiLu, this));
    auto jilumenu = Menu::create(menuImage2,NULL);
    jilumenu->setPosition(740,670);
    addChild(jilumenu);
    
    auto daikaibill = MenuItemImage::create("agency/dk_js_jl_1.png","agency/dk_js_jl_2.png",CC_CALLBACK_0(AgencyLayer::showAgencyBill, this));
    auto agencyBtn = Menu::create(daikaibill,NULL);
    agencyBtn->setPosition(185,645);
    addChild(agencyBtn);
    
    roomLayer = AgencyRoom::create();
    addChild(roomLayer);
    
    recordLayer = AgencyRecord::create();
    recordLayer->setVisible(false);
    addChild(recordLayer);
    
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
    
    return true;
}

void AgencyLayer::showAgencyBill(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendAgencyResult());
}

void AgencyLayer::updateData(){
    if(roomLayer->isVisible()){
        roomLayer->updateData();
    }
    if(recordLayer->isVisible()){
        recordLayer->updateData();
    }
}

void AgencyLayer::showYiKai(){
    if(NULL != getChildByTag(1115)){
        getChildByTag(1115)->setVisible(true);
    }
    if(NULL != getChildByTag(1116)){
        ((Sprite*)getChildByTag(1116))->setTexture("agency/yikai_2.png");
    }
    if(NULL != getChildByTag(1117)){
        getChildByTag(1117)->setVisible(false);
    }
    if(NULL != getChildByTag(1118)){
        ((Sprite*)getChildByTag(1118))->setTexture("agency/jilu_1.png");
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendAgencyInfo("0"));
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendAgencyInfo("1"));
    roomLayer->setVisible(true);
    roomLayer->updateData();
    recordLayer->setVisible(false);
}

void AgencyLayer::showJiLu(){
    if(NULL != getChildByTag(1115)){
        getChildByTag(1115)->setVisible(false);
    }
    if(NULL != getChildByTag(1116)){
        ((Sprite*)getChildByTag(1116))->setTexture("agency/yikai_1.png");
    }
    if(NULL != getChildByTag(1117)){
        getChildByTag(1117)->setVisible(true);
    }
    if(NULL != getChildByTag(1118)){
        ((Sprite*)getChildByTag(1118))->setTexture("agency/jilu_2.png");
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendAgencyInfo("1"));
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendAgencyInfo("0"));
    roomLayer->setVisible(false);
    recordLayer->setVisible(true);
    recordLayer->updateData();
}

void AgencyLayer::closeView(){
    removeFromParent();
}



