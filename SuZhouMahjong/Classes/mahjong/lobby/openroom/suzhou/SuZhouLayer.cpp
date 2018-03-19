//
//  SuZhouLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#include "mahjong/lobby/openroom/suzhou/SuZhouLayer.hpp"
#include "mahjong/lobby/openroom/FriendOpenRoom.h"
#include "mahjong/common/state/GameData.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "mahjong/GameConfig.h"


bool SuZhouLayer::init(){
    if(!Layer::init()){
        return false;
    }
    
    auto suZhouRoomText = Sprite::create("openroom/suzhou_text.png");
    suZhouRoomText->setPosition(745,355);
    addChild(suZhouRoomText);
    
    //滴零
    auto di_bg_1 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(SuZhouLayer::selectDiLing, this));
    auto menuDiLing = Menu::create(di_bg_1,NULL);
    menuDiLing->setPosition(460,345);
    addChild(menuDiLing);
    auto diLingImg = Sprite::create("openroom/icon_right.png");
    diLingImg->setTag(2001);
    diLingImg->setPosition(460,345);
    diLingImg->setVisible(true);
    addChild(diLingImg);
    
    //豪七
    auto di_bg_2 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(SuZhouLayer::selectHaoQi, this));
    auto menuHaoQi = Menu::create(di_bg_2,NULL);
    menuHaoQi->setPosition(655,345);
    addChild(menuHaoQi);
    auto haoQiImg = Sprite::create("openroom/icon_right.png");
    haoQiImg->setTag(2002);
    haoQiImg->setPosition(655,345);
    haoQiImg->setVisible(false);
    addChild(haoQiImg);
    
    /* 房间局数选择 */
    auto fangka8 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(SuZhouLayer::selectFangka8, this));
    auto fangka8Menu = Menu::create(fangka8,NULL);
    fangka8Menu->setPosition(460,253);
    addChild(fangka8Menu);
    
    auto select8 = Sprite::create("openroom/circle_select.png");
    select8->setTag(1024);
    select8->setPosition(460,253);
    select8->setVisible(true);
    addChild(select8);
    
    auto fangka4 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(SuZhouLayer::selectFangka4, this));
    auto fangka4Menu = Menu::create(fangka4,NULL);
    fangka4Menu->setPosition(660,253);
    addChild(fangka4Menu);
    
    auto select4 = Sprite::create("openroom/circle_select.png");
    select4->setTag(1025);
    select4->setPosition(660,253);
    select4->setVisible(false);
    addChild(select4);
    
    auto fangka16 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(SuZhouLayer::selectFangka16, this));
    auto fangka16Menu = Menu::create(fangka16,NULL);
    fangka16Menu->setPosition(850,253);
    addChild(fangka16Menu);
    
    auto select16 = Sprite::create("openroom/circle_select.png");
    select16->setTag(1026);
    select16->setPosition(850,253);
    select16->setVisible(false);
    addChild(select16);
    
    
    
    auto payByFZImg = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(SuZhouLayer::selectFZ, this));
    auto payByFZ = Menu::create(payByFZImg,NULL);
    payByFZ->setPosition(460,175);
    addChild(payByFZ);
    
    auto selectFZ = Sprite::create("openroom/circle_select.png");
    selectFZ->setTag(3024);
    selectFZ->setPosition(460,175);
    selectFZ->setVisible(true);
    addChild(selectFZ);
    
    auto payByAAImg = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(SuZhouLayer::selectAA, this));
    auto payByAAMenu = Menu::create(payByAAImg,NULL);
    payByAAMenu->setPosition(660,175);
    addChild(payByAAMenu);
    
    auto selectAA = Sprite::create("openroom/circle_select.png");
    selectAA->setTag(3025);
    selectAA->setPosition(660,175);
    selectAA->setVisible(false);
    addChild(selectAA);
    

    
    //开房消耗显示
    auto fangka = Label::createWithSystemFont(StringUtils::format("X%0.1f",atof(GAMEDATA::getInstance()->getKaiFangXiaoHao8().c_str())), "arial", 26);
    fangka->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fangka->setColor(Color3B(124,37,7));
    fangka->setPosition(975,175);
    fangka->setTag(1314);
    addChild(fangka);
//    auto xiaohao = Sprite::create("openroom/fang_fee_text.png");
//    xiaohao->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    xiaohao->setTag(1315);
//    xiaohao->setPosition(fangka->getPositionX()+fangka->getContentSize().width,177);
//    addChild(xiaohao);
    
    showOpenRoomBtn();//显示开设房间按钮
    
    //按照记录显示用户的习惯
    if(UserData::getInstance()->getLatelyGameJuShu()=="4"){
        selectFangka4();
    }else if(UserData::getInstance()->getLatelyGameJuShu()=="16"){
        selectFangka16();
    }else{
        selectFangka8();
    }
    if(UserData::getInstance()->getLatelySZHaoQi() == "1"){
        haoQiImg->setVisible(true);
    }else{
        haoQiImg->setVisible(false);
    }
    if(UserData::getInstance()->getLatelySZDiLing() == "1"){
        diLingImg->setVisible(true);
    }else{
        diLingImg->setVisible(false);
    }
    if(UserData::getInstance()->getLatelyPayWayAA()){
        SuZhouLayer::selectAA();
    }else{
        SuZhouLayer::selectFZ();
    }
    
    return true;
}

void SuZhouLayer::showOpenRoomBtn(){
    auto openBtn = MenuItemImage::create("openroom/open_room_btn_img_1.png", "openroom/open_room_btn_img_2.png", CC_CALLBACK_0(SuZhouLayer::openRoom, this));
    auto openMenu = Menu::create(openBtn,NULL);
    openMenu->setPosition(640,85);
    addChild(openMenu);
    
    if(UserData::getInstance()->getIsAgency()){
        openMenu->setPosition(300,85);
        
        auto agencyBtn = MenuItemImage::create("openroom/angecy_open_room_1.png", "openroom/angecy_open_room_2.png", CC_CALLBACK_0(SuZhouLayer::openRoomByAgency, this));
        auto agencyMenu = Menu::create(agencyBtn,NULL);
        agencyMenu->setPosition(640,85);
        addChild(agencyMenu);
        
        auto manageBtn = MenuItemImage::create("openroom/angecy_manage_room_1.png", "openroom/angecy_manage_room_2.png", CC_CALLBACK_0(SuZhouLayer::checkAgencyRecord, this));
        auto manageMenu = Menu::create(manageBtn,NULL);
        manageMenu->setPosition(990,85);
        addChild(manageMenu);
    }
}

void SuZhouLayer::selectDiLing(){
    if(NULL != getChildByTag(2001)){
        getChildByTag(2001)->setVisible(!getChildByTag(2001)->isVisible());
    }
}

void SuZhouLayer::selectHaoQi(){
    if(NULL != getChildByTag(2002)){
        getChildByTag(2002)->setVisible(!getChildByTag(2002)->isVisible());
    }
}

std::string SuZhouLayer::getHaoQi(){
    std::string haoqi = "0";
    if(NULL != getChildByTag(2002)){
        if(getChildByTag(2002)->isVisible()){
            haoqi = "1";
        }else{
            haoqi = "0";
        }
    }
    return haoqi;
}

std::string SuZhouLayer::getDiLing(){
    std::string diling = "1";
    if(NULL != getChildByTag(2001)){
        if(getChildByTag(2001)->isVisible()){
            diling = "1";
        }else{
            diling = "0";
        }
    }
    return diling;
}

void SuZhouLayer::selectFangka8(){
    if(NULL != getChildByTag(1024)){
        getChildByTag(1024)->setVisible(true);
    }
    if(NULL != getChildByTag(1025)){
        getChildByTag(1025)->setVisible(false);
    }
    if(NULL != getChildByTag(1026)){
        getChildByTag(1026)->setVisible(false);
    }
    float num = atof(GAMEDATA::getInstance()->getKaiFangXiaoHao8().c_str());
    if(getPayWay() == "-1"){
        num = num/4.0;
    }
    ((Label*)getChildByTag(1314))->setString(StringUtils::format("X%0.1f",num));
//    getChildByTag(1315)->setPosition(getChildByTag(1314)->getPositionX()+getChildByTag(1314)->getContentSize().width,177);
}

void SuZhouLayer::selectFangka4(){
    if(NULL != getChildByTag(1024)){
        getChildByTag(1024)->setVisible(false);
    }
    if(NULL != getChildByTag(1025)){
        getChildByTag(1025)->setVisible(true);
    }
    if(NULL != getChildByTag(1026)){
        getChildByTag(1026)->setVisible(false);
    }
    float num = atof(GAMEDATA::getInstance()->getKaiFangXiaoHao4().c_str());
    if(getPayWay() == "-1"){
        num = num/4.0;
    }
    ((Label*)getChildByTag(1314))->setString(StringUtils::format("X%0.1f",num));
//    getChildByTag(1315)->setPosition(getChildByTag(1314)->getPositionX()+getChildByTag(1314)->getContentSize().width,177);
}

void SuZhouLayer::selectFangka16(){
    if(NULL != getChildByTag(1024)){
        getChildByTag(1024)->setVisible(false);
    }
    if(NULL != getChildByTag(1025)){
        getChildByTag(1025)->setVisible(false);
    }
    if(NULL != getChildByTag(1026)){
        getChildByTag(1026)->setVisible(true);
    }
    float num = atof(GAMEDATA::getInstance()->getKaiFangXiaoHao16().c_str());
    if(getPayWay() == "-1"){
        num = num/4.0;
    }
    ((Label*)getChildByTag(1314))->setString(StringUtils::format("X%0.1f",num));
//    getChildByTag(1315)->setPosition(getChildByTag(1314)->getPositionX()+getChildByTag(1314)->getContentSize().width,177);
}

void SuZhouLayer::selectAA(){
    if(NULL != getChildByTag(3025)){
        getChildByTag(3025)->setVisible(true);
    }
    if(NULL != getChildByTag(3024)){
        getChildByTag(3024)->setVisible(false);
    }
    float num = 0;
    if(getOpenRoomJuShu() == "3"){
        num = atof(GAMEDATA::getInstance()->getKaiFangXiaoHao16().c_str());
    }else if(getOpenRoomJuShu() == "2"){
        num = atof(GAMEDATA::getInstance()->getKaiFangXiaoHao4().c_str());
    }else{
        num = atof(GAMEDATA::getInstance()->getKaiFangXiaoHao8().c_str());
    }
    ((Label*)getChildByTag(1314))->setString(StringUtils::format("X%.1f",num/4.0));
}

void SuZhouLayer::selectFZ(){
    if(NULL != getChildByTag(3025)){
        getChildByTag(3025)->setVisible(false);
    }
    if(NULL != getChildByTag(3024)){
        getChildByTag(3024)->setVisible(true);
    }
    float num = 0;
    if(getOpenRoomJuShu() == "3"){
        num = atof(GAMEDATA::getInstance()->getKaiFangXiaoHao16().c_str());
    }else if(getOpenRoomJuShu() == "2"){
        num = atof(GAMEDATA::getInstance()->getKaiFangXiaoHao4().c_str());
    }else{
        num = atof(GAMEDATA::getInstance()->getKaiFangXiaoHao8().c_str());
    }
    ((Label*)getChildByTag(1314))->setString(StringUtils::format("X%0.1f",num));
}

std::string SuZhouLayer::getPayWay(){
    std::string payway = "";
    if(NULL != getChildByTag(3024)&& NULL != getChildByTag(3025)){
        if(getChildByTag(3025)->isVisible()){
            payway = "-1";
        }else{
            payway = "";
        }
    }
    return payway;
}

std::string SuZhouLayer::getOpenRoomJuShu(){
    std::string ftype = "1";//1表示8局，2表示4局，3表示16局
    if(NULL != getChildByTag(1024)&& NULL != getChildByTag(1025)&& NULL != getChildByTag(1026)){
        if(getChildByTag(1025)->isVisible()){
            ftype = "2";
        }else if(getChildByTag(1026)->isVisible()){
            ftype = "3";
        }else{
            ftype = "1";
        }
    }
    return ftype;
}

void SuZhouLayer::openRoom(){
    std::string ftype = getOpenRoomJuShu();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOpenRoomCommand(ftype,getHaoQi(),getDiLing(),ROOM_SIZE,getPayWay()));
}

void SuZhouLayer::openRoomByAgency(){
    std::string ftype = getOpenRoomJuShu();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOpenRoomCommand(ftype,getHaoQi(),getDiLing(),ROOM_SIZE,UserData::getInstance()->getPoxiaoId()));
}

void SuZhouLayer::checkAgencyRecord(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendAgencyInfo("0"));
}


