//
//  ShangHaiSelectLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#include "mahjong/lobby/friend/chongming/ChongMingSelectLayer.hpp"
#include "server/NetworkManage.h"
#include "mahjong/common/state/GameData.h"
#include "userdata/UserData.h"


bool ChongMingSelectLayer::init(){
    if(!Layer::init()){
        return false;
    }
    
    
    auto shangHaiRoomText = Sprite::create("openroom/chong_ming_text.png");
    shangHaiRoomText->setPosition(745,355);
    addChild(shangHaiRoomText);
    
    /* 底和花的选择  */
    auto di_bg_1 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(ChongMingSelectLayer::selectDiHua11, this));
    auto menuDi_1 = Menu::create(di_bg_1,NULL);
    menuDi_1->setPosition(455,568);
    addChild(menuDi_1);
    //底花1/1
    auto diHuaImg11 = Sprite::create("openroom/circle_select.png");
    diHuaImg11->setTag(2001);
    diHuaImg11->setPosition(455,568);
    diHuaImg11->setVisible(true);
    addChild(diHuaImg11);
    
    
    auto di_bg_2 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(ChongMingSelectLayer::selectDiHua22, this));
    auto menuDi_2 = Menu::create(di_bg_2,NULL);
    menuDi_2->setPosition(655,568);
    addChild(menuDi_2);
    //底花2/2
    auto diHuaImg22 = Sprite::create("openroom/circle_select.png");
    diHuaImg22->setTag(2002);
    diHuaImg22->setPosition(655,568);
    diHuaImg22->setVisible(false);
    addChild(diHuaImg22);
    
    
    auto di_bg_3 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(ChongMingSelectLayer::selectDiHua62, this));
    auto menuDi_3 = Menu::create(di_bg_3,NULL);
    menuDi_3->setPosition(845,568);
    addChild(menuDi_3);
    //底花6/2
    auto diHuaImg62 = Sprite::create("openroom/circle_select.png");
    diHuaImg62->setTag(2003);
    diHuaImg62->setPosition(845,568);
    diHuaImg62->setVisible(false);
    addChild(diHuaImg62);
    
    
    auto di_bg_4 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(ChongMingSelectLayer::selectDiHua55, this));
    auto menuDi_4 = Menu::create(di_bg_4,NULL);
    menuDi_4->setPosition(1020,568);
    addChild(menuDi_4);
    //底花5/5
    auto diHuaImg55 = Sprite::create("openroom/circle_select.png");
    diHuaImg55->setTag(2004);
    diHuaImg55->setPosition(1020,568);
    diHuaImg55->setVisible(false);
    addChild(diHuaImg55);
    
    /* 勒子选择 */
    auto le_bg_1 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(ChongMingSelectLayer::selectLezi20, this));
    auto menuLe_1 = Menu::create(le_bg_1,NULL);
    menuLe_1->setPosition(455,495);
    addChild(menuLe_1);
    // 20勒子
    auto leZhiImg20 = Sprite::create("openroom/circle_select.png");
    leZhiImg20->setTag(3001);
    leZhiImg20->setPosition(455,495);
    leZhiImg20->setVisible(true);
    addChild(leZhiImg20);
    
    auto le_bg_2 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(ChongMingSelectLayer::selectLezi50, this));
    auto menuLe_2 = Menu::create(le_bg_2,NULL);
    menuLe_2->setPosition(655,495);
    addChild(menuLe_2);
    // 50勒子
    auto leZhiImg50 = Sprite::create("openroom/circle_select.png");
    leZhiImg50->setTag(3002);
    leZhiImg50->setPosition(655,495);
    leZhiImg50->setVisible(false);
    addChild(leZhiImg50);
    
    auto le_bg_3 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(ChongMingSelectLayer::selectLezi100, this));
    auto menuLe_3 = Menu::create(le_bg_3,NULL);
    menuLe_3->setPosition(845,495);
    addChild(menuLe_3);
    // 100勒子
    auto leZhiImg100 = Sprite::create("openroom/circle_select.png");
    leZhiImg100->setTag(3003);
    leZhiImg100->setPosition(845,495);
    leZhiImg100->setVisible(false);
    addChild(leZhiImg100);
    
    auto le_bg_4 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(ChongMingSelectLayer::selectLeziWu, this));
    auto menuLe_4 = Menu::create(le_bg_4,NULL);
    menuLe_4->setPosition(1020,495);
    addChild(menuLe_4);
    // 20勒子
    auto leZhiImgWu = Sprite::create("openroom/circle_select.png");
    leZhiImgWu->setTag(3004);
    leZhiImgWu->setPosition(1020,495);
    leZhiImgWu->setVisible(false);
    addChild(leZhiImgWu);
    
    
    //开宝
    auto wukaibao = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(ChongMingSelectLayer::selectWukaibao, this));
    auto wukaibaoMenu = Menu::create(wukaibao,NULL);
    wukaibaoMenu->setPosition(460,420);
    addChild(wukaibaoMenu);
    
    auto selectWukaibao = Sprite::create("openroom/icon_right.png");
    selectWukaibao->setTag(4001);
    selectWukaibao->setPosition(460,420);
    selectWukaibao->setVisible(true);
    addChild(selectWukaibao);
    
    //飞苍蝇
    auto feicy = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(ChongMingSelectLayer::selectFeiChangYin, this));
    auto feicyMenu = Menu::create(feicy,NULL);
    feicyMenu->setPosition(655,420);
    addChild(feicyMenu);
    
    auto selectFeicy = Sprite::create("openroom/icon_right.png");
    selectFeicy->setTag(4002);
    selectFeicy->setPosition(655,420);
    selectFeicy->setVisible(false);
    addChild(selectFeicy);
    
    //显示用户的日常习惯
    if(UserData::getInstance()->getLatelySHDiHua() == "0"){
        selectDiHua11();
    }else if(UserData::getInstance()->getLatelySHDiHua() == "1"){
        selectDiHua22();
    }else if(UserData::getInstance()->getLatelySHDiHua() == "2"){
        selectDiHua62();
    } else if(UserData::getInstance()->getLatelySHDiHua() == "3"){
        selectDiHua55();
    }
    if(UserData::getInstance()->getLatelySHLeZhi() == "0"){
        selectLezi20();
    }else if(UserData::getInstance()->getLatelySHLeZhi() == "1"){
        selectLezi50();
    }else if(UserData::getInstance()->getLatelySHLeZhi() == "2"){
        selectLezi100();
    }else if(UserData::getInstance()->getLatelySHLeZhi() == "3"){
        selectLeziWu();
    }
    if(UserData::getInstance()->getLatelySHKaiBao() == "0"){
        if(NULL != getChildByTag(4001)){
            getChildByTag(4001)->setVisible(false);
        }
    }else{
        if(NULL != getChildByTag(4001)){
            getChildByTag(4001)->setVisible(true);
        }
    }
    if(UserData::getInstance()->getLatelySHFcy() == "0"){
        if(NULL != getChildByTag(4002)){
            getChildByTag(4002)->setVisible(false);
        }
    }else{
        if(NULL != getChildByTag(4002)){
            getChildByTag(4002)->setVisible(true);
        }
    }

    
    return true;
}


void ChongMingSelectLayer::selectDiHua11(){
    if(NULL != getChildByTag(2001)){
        getChildByTag(2001)->setVisible(true);
    }
    if(NULL != getChildByTag(2002)){
        getChildByTag(2002)->setVisible(false);
    }
    if(NULL != getChildByTag(2003)){
        getChildByTag(2003)->setVisible(false);
    }
    if(NULL != getChildByTag(2004)){
        getChildByTag(2004)->setVisible(false);
    }
    selectLezi20();
}

void ChongMingSelectLayer::selectDiHua22(){
    if(NULL != getChildByTag(2001)){
        getChildByTag(2001)->setVisible(false);
    }
    if(NULL != getChildByTag(2002)){
        getChildByTag(2002)->setVisible(true);
    }
    if(NULL != getChildByTag(2003)){
        getChildByTag(2003)->setVisible(false);
    }
    if(NULL != getChildByTag(2004)){
        getChildByTag(2004)->setVisible(false);
    }
    selectLezi50();
}

void ChongMingSelectLayer::selectDiHua62(){
    if(NULL != getChildByTag(2001)){
        getChildByTag(2001)->setVisible(false);
    }
    if(NULL != getChildByTag(2002)){
        getChildByTag(2002)->setVisible(false);
    }
    if(NULL != getChildByTag(2003)){
        getChildByTag(2003)->setVisible(true);
    }
    if(NULL != getChildByTag(2004)){
        getChildByTag(2004)->setVisible(false);
    }
    selectLezi50();
}

void ChongMingSelectLayer::selectDiHua55(){
    if(NULL != getChildByTag(2001)){
        getChildByTag(2001)->setVisible(false);
    }
    if(NULL != getChildByTag(2002)){
        getChildByTag(2002)->setVisible(false);
    }
    if(NULL != getChildByTag(2003)){
        getChildByTag(2003)->setVisible(false);
    }
    if(NULL != getChildByTag(2004)){
        getChildByTag(2004)->setVisible(true);
    }
    selectLezi100();
}

void ChongMingSelectLayer::selectLezi20(){
    if(NULL != getChildByTag(3001)){
        getChildByTag(3001)->setVisible(true);
    }
    if(NULL != getChildByTag(3002)){
        getChildByTag(3002)->setVisible(false);
    }
    if(NULL != getChildByTag(3003)){
        getChildByTag(3003)->setVisible(false);
    }
    if(NULL != getChildByTag(3004)){
        getChildByTag(3004)->setVisible(false);
    }
}

void ChongMingSelectLayer::selectLezi50(){
    if(NULL != getChildByTag(3001)){
        getChildByTag(3001)->setVisible(false);
    }
    if(NULL != getChildByTag(3002)){
        getChildByTag(3002)->setVisible(true);
    }
    if(NULL != getChildByTag(3003)){
        getChildByTag(3003)->setVisible(false);
    }
    if(NULL != getChildByTag(3004)){
        getChildByTag(3004)->setVisible(false);
    }
}

void ChongMingSelectLayer::selectLezi100(){
    if(NULL != getChildByTag(3001)){
        getChildByTag(3001)->setVisible(false);
    }
    if(NULL != getChildByTag(3002)){
        getChildByTag(3002)->setVisible(false);
    }
    if(NULL != getChildByTag(3003)){
        getChildByTag(3003)->setVisible(true);
    }
    if(NULL != getChildByTag(3004)){
        getChildByTag(3004)->setVisible(false);
    }
}

void ChongMingSelectLayer::selectLeziWu(){
    if(NULL != getChildByTag(3001)){
        getChildByTag(3001)->setVisible(false);
    }
    if(NULL != getChildByTag(3002)){
        getChildByTag(3002)->setVisible(false);
    }
    if(NULL != getChildByTag(3003)){
        getChildByTag(3003)->setVisible(false);
    }
    if(NULL != getChildByTag(3004)){
        getChildByTag(3004)->setVisible(true);
    }
}

void ChongMingSelectLayer::selectWukaibao(){
    if(NULL != getChildByTag(4001)){
        getChildByTag(4001)->setVisible(!getChildByTag(4001)->isVisible());
    }
}

void ChongMingSelectLayer::selectFeiChangYin(){
    if(NULL != getChildByTag(4002)){
        getChildByTag(4002)->setVisible(!getChildByTag(4002)->isVisible());
    }
}

std::string ChongMingSelectLayer::getDiHua(){
    std::string dihua = "0";//0表示1/1 ,   1 表示 2/2 ,2表示 6/2 ,3表示 5/5
    if(NULL != getChildByTag(2001)&&getChildByTag(2001)->isVisible()){
        dihua = "0";
    }else if(NULL != getChildByTag(2002)&&getChildByTag(2002)->isVisible()){
        dihua = "1";
    }else if(NULL != getChildByTag(2003)&&getChildByTag(2003)->isVisible()){
        dihua = "2";
    }
    else if(NULL != getChildByTag(2004)&&getChildByTag(2004)->isVisible()){
        dihua = "3";
    }
    return dihua;
}

std::string ChongMingSelectLayer::getLeizi(){
    std::string iflezi = "0";//0表示20,1表示50,2表示100,3表示无勒子
    if(NULL != getChildByTag(3001)&&getChildByTag(3001)->isVisible()){
        iflezi = "0";
    }else if(NULL != getChildByTag(3002)&&getChildByTag(3002)->isVisible()){
        iflezi = "1";
    }else if(NULL != getChildByTag(3003)&&getChildByTag(3003)->isVisible()){
        iflezi = "2";
    }
    else if(NULL != getChildByTag(3004)&&getChildByTag(3004)->isVisible()){
        iflezi = "3";
    }
    return iflezi ;
}

std::string ChongMingSelectLayer::getKaibao(){
    std::string ifkb = "1";//0表示没有，1表示有
    if(NULL != getChildByTag(4001)){
        if(getChildByTag(4001)->isVisible()){
            ifkb = "1";
        }else{
            ifkb = "0";
        }
    }
    return ifkb;
}

std::string ChongMingSelectLayer::getFeiChangYin(){
    std::string ifcy = "0";//0表示没有，1表示有
    if(NULL != getChildByTag(4002)){
        if(getChildByTag(4002)->isVisible()){
            ifcy = "1";
        }else{
            ifcy = "0";
        }
    }
    return ifcy;
}



