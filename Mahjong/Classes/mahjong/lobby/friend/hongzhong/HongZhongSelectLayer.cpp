//
//  HongZhongSelectLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#include "mahjong/lobby/friend/hongzhong/HongZhongSelectLayer.hpp"
#include "server/NetworkManage.h"
#include "mahjong/common/state/GameData.h"
#include "userdata/UserData.h"

bool HongZhongSelectLayer::init(){
    if(!Layer::init()){
        return false;
    }
    
    auto hongZhongRoomText = Sprite::create("openroom/hong_zhong_text.png");
    hongZhongRoomText->setPosition(745,355);
    addChild(hongZhongRoomText);
    
    /* 底和花的选择  */
    auto di_bg_1 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(HongZhongSelectLayer::selectDifen2, this));
    auto menuDi_1 = Menu::create(di_bg_1,NULL);
    menuDi_1->setPosition(455,568);
    addChild(menuDi_1);
    //底花1/1
    auto diHuaImg11 = Sprite::create("openroom/circle_select.png");
    diHuaImg11->setTag(2001);
    diHuaImg11->setPosition(455,568);
    diHuaImg11->setVisible(true);
    addChild(diHuaImg11);
    
    
    auto di_bg_2 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(HongZhongSelectLayer::selectDifen1, this));
    auto menuDi_2 = Menu::create(di_bg_2,NULL);
    menuDi_2->setPosition(655,568);
    addChild(menuDi_2);
    //底花2/2
    auto diHuaImg22 = Sprite::create("openroom/circle_select.png");
    diHuaImg22->setTag(2002);
    diHuaImg22->setPosition(655,568);
    diHuaImg22->setVisible(false);
    addChild(diHuaImg22);
    
    
    auto di_bg_3 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(HongZhongSelectLayer::selectDifen5, this));
    auto menuDi_3 = Menu::create(di_bg_3,NULL);
    menuDi_3->setPosition(845,568);
    addChild(menuDi_3);
    //底花6/2
    auto diHuaImg62 = Sprite::create("openroom/circle_select.png");
    diHuaImg62->setTag(2003);
    diHuaImg62->setPosition(845,568);
    diHuaImg62->setVisible(false);
    addChild(diHuaImg62);
    
    
    auto ma159zh = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(HongZhongSelectLayer::selectMa159zh, this));
    auto ma159zhMenu = Menu::create(ma159zh,NULL);
    ma159zhMenu->setPosition(455,420);
    addChild(ma159zhMenu);
    
    auto ma159zhImg = Sprite::create("openroom/icon_right.png");
    ma159zhImg->setTag(3001);
    ma159zhImg->setPosition(455,420);
    addChild(ma159zhImg);
    
    auto ma159 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(HongZhongSelectLayer::selectMa159, this));
    auto ma159Menu = Menu::create(ma159,NULL);
    ma159Menu->setPosition(765,420);
    addChild(ma159Menu);
    
    auto ma159Img = Sprite::create("openroom/icon_right.png");
    ma159Img->setPosition(765,420);
    ma159Img->setTag(3002);
    ma159Img->setVisible(false);
    addChild(ma159Img);
    
    auto ma1 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(HongZhongSelectLayer::selectMa1, this));
    auto ma1Menu = Menu::create(ma1,NULL);
    ma1Menu->setPosition(1020,420);
    addChild(ma1Menu);
    
    auto ma1Img = Sprite::create("openroom/icon_right.png");
    ma1Img->setTag(3003);
    ma1Img->setPosition(1020,420);
    ma1Img->setVisible(false);
    addChild(ma1Img);
    
    //显示用户的日常习惯
    if(UserData::getInstance()->getLatelyHZDi() == "2"){
        selectDifen2();
    }else if(UserData::getInstance()->getLatelyHZDi() == "1"){
        selectDifen1();
    }else if(UserData::getInstance()->getLatelyHZDi() == "5"){
        selectDifen5();
    }
    if(UserData::getInstance()->getLatelyHZFanMa() == "4"){
        selectMa159zh();
    }else if(UserData::getInstance()->getLatelyHZFanMa() == "3"){
        selectMa159();
    }else if(UserData::getInstance()->getLatelyHZFanMa() == "1"){
        selectMa1();
    }
    
    return true;
}

void HongZhongSelectLayer::selectMa159zh(){
    if(NULL != getChildByTag(3001)){
        getChildByTag(3001)->setVisible(true);
    }
    if(NULL != getChildByTag(3002)){
        getChildByTag(3002)->setVisible(false);
    }
    if(NULL != getChildByTag(3003)){
        getChildByTag(3003)->setVisible(false);
    }
}


void HongZhongSelectLayer::selectMa159(){
    if(NULL != getChildByTag(3001)){
        getChildByTag(3001)->setVisible(false);
    }
    if(NULL != getChildByTag(3002)){
        getChildByTag(3002)->setVisible(true);
    }
    if(NULL != getChildByTag(3003)){
        getChildByTag(3003)->setVisible(false);
    }
}

void HongZhongSelectLayer::selectMa1(){
    if(NULL != getChildByTag(3001)){
        getChildByTag(3001)->setVisible(false);
    }
    if(NULL != getChildByTag(3002)){
        getChildByTag(3002)->setVisible(false);
    }
    if(NULL != getChildByTag(3003)){
        getChildByTag(3003)->setVisible(true);
    }
}

void HongZhongSelectLayer::selectDifen2(){
    if(NULL != getChildByTag(2001)){
        getChildByTag(2001)->setVisible(true);
    }
    if(NULL != getChildByTag(2002)){
        getChildByTag(2002)->setVisible(false);
    }
    if(NULL != getChildByTag(2003)){
        getChildByTag(2003)->setVisible(false);
    }
}


void HongZhongSelectLayer::selectDifen1(){
    if(NULL != getChildByTag(2001)){
        getChildByTag(2001)->setVisible(false);
    }
    if(NULL != getChildByTag(2002)){
        getChildByTag(2002)->setVisible(true);
    }
    if(NULL != getChildByTag(2003)){
        getChildByTag(2003)->setVisible(false);
    }
}

void HongZhongSelectLayer::selectDifen5(){
    if(NULL != getChildByTag(2001)){
        getChildByTag(2001)->setVisible(false);
    }
    if(NULL != getChildByTag(2002)){
        getChildByTag(2002)->setVisible(false);
    }
    if(NULL != getChildByTag(2003)){
        getChildByTag(2003)->setVisible(true);
    }
}

std::string HongZhongSelectLayer::getFanMa(){
    std::string fanma = "0";//0表示没有159zhong,1表示有159,2表示1码
    
    if(NULL != getChildByTag(3001)&&getChildByTag(3001)->isVisible()){
        fanma  = "4";
    }else if(NULL != getChildByTag(3002)&&getChildByTag(3002)->isVisible()){
        fanma  = "3";
    }else if(NULL != getChildByTag(3003)&&getChildByTag(3003)->isVisible()){
        fanma  = "1";
    }
    return fanma;
}

std::string HongZhongSelectLayer::getDiFen(){
    std::string difen = "2";
    if(NULL != getChildByTag(2001)&&getChildByTag(2001)->isVisible()){
        difen = "2";
    }else if(NULL != getChildByTag(2002)&&getChildByTag(2002)->isVisible()){
        difen = "1";
    }else if(NULL != getChildByTag(2003)&&getChildByTag(2003)->isVisible()){
        difen = "5";
    }
    return difen;
}
