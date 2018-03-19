//
//  HongZhongLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#include "mahjong/lobby/openroom/hongzhong/HongZhongLayer.hpp"
#include "mahjong/lobby/openroom/FriendOpenRoom.h"
#include "mahjong/common/state/GameData.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "mahjong/GameConfig.h"

bool HongZhongLayer::init(){
    if(!Layer::init()){
        return false;
    }
    
    auto hongZhongRoomText = Sprite::create("openroom/hong_zhong_text.png");
    hongZhongRoomText->setPosition(745,355);
    addChild(hongZhongRoomText);
    
    /* 底和花的选择  */
    auto di_bg_1 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(HongZhongLayer::selectDifen2, this));
    auto menuDi_1 = Menu::create(di_bg_1,NULL);
    menuDi_1->setPosition(455,548);
    addChild(menuDi_1);
    //底花1/1
    auto diHuaImg11 = Sprite::create("openroom/circle_select.png");
    diHuaImg11->setTag(2001);
    diHuaImg11->setPosition(455,548);
    diHuaImg11->setVisible(true);
    addChild(diHuaImg11);
    
    
    auto di_bg_2 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(HongZhongLayer::selectDifen1, this));
    auto menuDi_2 = Menu::create(di_bg_2,NULL);
    menuDi_2->setPosition(655,548);
    addChild(menuDi_2);
    //底花2/2
    auto diHuaImg22 = Sprite::create("openroom/circle_select.png");
    diHuaImg22->setTag(2002);
    diHuaImg22->setPosition(655,548);
    diHuaImg22->setVisible(false);
    addChild(diHuaImg22);
    
    
    auto di_bg_3 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(HongZhongLayer::selectDifen5, this));
    auto menuDi_3 = Menu::create(di_bg_3,NULL);
    menuDi_3->setPosition(845,548);
    addChild(menuDi_3);
    //底花6/2
    auto diHuaImg62 = Sprite::create("openroom/circle_select.png");
    diHuaImg62->setTag(2003);
    diHuaImg62->setPosition(845,548);
    diHuaImg62->setVisible(false);
    addChild(diHuaImg62);
    
    
    auto ma159zh = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(HongZhongLayer::selectMa159zh, this));
    auto ma159zhMenu = Menu::create(ma159zh,NULL);
    ma159zhMenu->setPosition(455,380);
    addChild(ma159zhMenu);
    
    auto ma159zhImg = Sprite::create("openroom/icon_right.png");
    ma159zhImg->setTag(3001);
    ma159zhImg->setPosition(455,380);
    addChild(ma159zhImg);
    
    auto ma159 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(HongZhongLayer::selectMa159, this));
    auto ma159Menu = Menu::create(ma159,NULL);
    ma159Menu->setPosition(765,380);
    addChild(ma159Menu);
    
    auto ma159Img = Sprite::create("openroom/icon_right.png");
    ma159Img->setPosition(765,380);
    ma159Img->setTag(3002);
    ma159Img->setVisible(false);
    addChild(ma159Img);
    
    auto ma1 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(HongZhongLayer::selectMa1, this));
    auto ma1Menu = Menu::create(ma1,NULL);
    ma1Menu->setPosition(1020,380);
    addChild(ma1Menu);
    
    auto ma1Img = Sprite::create("openroom/icon_right.png");
    ma1Img->setTag(3003);
    ma1Img->setPosition(1020,380);
    ma1Img->setVisible(false);
    addChild(ma1Img);
    
    /* 房间局数选择 */
    auto fangka8 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(HongZhongLayer::selectFangka8, this));
    auto fangka8Menu = Menu::create(fangka8,NULL);
    fangka8Menu->setPosition(460,253);
    addChild(fangka8Menu);
    
    auto select8 = Sprite::create("openroom/circle_select.png");
    select8->setTag(1024);
    select8->setPosition(460,253);
    select8->setVisible(true);
    addChild(select8);
    
    auto fangka4 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(HongZhongLayer::selectFangka4, this));
    auto fangka4Menu = Menu::create(fangka4,NULL);
    fangka4Menu->setPosition(660,253);
    addChild(fangka4Menu);
    
    auto select4 = Sprite::create("openroom/circle_select.png");
    select4->setTag(1025);
    select4->setPosition(660,253);
    select4->setVisible(false);
    addChild(select4);
    
    auto fangka16 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(HongZhongLayer::selectFangka16, this));
    auto fangka16Menu = Menu::create(fangka16,NULL);
    fangka16Menu->setPosition(850,253);
    addChild(fangka16Menu);
    
    auto select16 = Sprite::create("openroom/circle_select.png");
    select16->setTag(1026);
    select16->setPosition(850,253);
    select16->setVisible(false);
    addChild(select16);
    
    auto payByFZImg = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(HongZhongLayer::selectFZ, this));
    auto payByFZ = Menu::create(payByFZImg,NULL);
    payByFZ->setPosition(460,175);
    addChild(payByFZ);
    
    auto selectFZ = Sprite::create("openroom/circle_select.png");
    selectFZ->setTag(3024);
    selectFZ->setPosition(460,175);
    selectFZ->setVisible(true);
    addChild(selectFZ);
    
    auto payByAAImg = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(HongZhongLayer::selectAA, this));
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
    
    showOpenRoomBtn();
    
    //显示用户的日常习惯
    if(UserData::getInstance()->getLatelyGameJuShu()=="4"){
        selectFangka4();
    }else if(UserData::getInstance()->getLatelyGameJuShu()=="16"){
        selectFangka16();
    }else{
        selectFangka8();
    }
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
    if(UserData::getInstance()->getLatelyPayWayAA()){
        HongZhongLayer::selectAA();
    }else{
        HongZhongLayer::selectFZ();
    }
    return true;
}

void HongZhongLayer::showOpenRoomBtn(){
    auto openBtn = MenuItemImage::create("openroom/open_room_btn_img_1.png", "openroom/open_room_btn_img_2.png", CC_CALLBACK_0(HongZhongLayer::openRoom, this));
    auto openMenu = Menu::create(openBtn,NULL);
    openMenu->setPosition(640,85);
    addChild(openMenu);
    
    if(UserData::getInstance()->getIsAgency()){
        openMenu->setPosition(300,85);
        
        auto agencyBtn = MenuItemImage::create("openroom/angecy_open_room_1.png", "openroom/angecy_open_room_2.png", CC_CALLBACK_0(HongZhongLayer::openRoomByAgency, this));
        auto agencyMenu = Menu::create(agencyBtn,NULL);
        agencyMenu->setPosition(640,85);
        addChild(agencyMenu);
        
        auto manageBtn = MenuItemImage::create("openroom/angecy_manage_room_1.png", "openroom/angecy_manage_room_2.png", CC_CALLBACK_0(HongZhongLayer::checkAgencyRecord, this));
        auto manageMenu = Menu::create(manageBtn,NULL);
        manageMenu->setPosition(990,85);
        addChild(manageMenu);
    }
}

void HongZhongLayer::selectMa159zh(){
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


void HongZhongLayer::selectMa159(){
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

void HongZhongLayer::selectMa1(){
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

void HongZhongLayer::selectDifen2(){
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


void HongZhongLayer::selectDifen1(){
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

void HongZhongLayer::selectDifen5(){
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

std::string HongZhongLayer::getFanMa(){
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

std::string HongZhongLayer::getDiFen(){
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

void HongZhongLayer::selectFangka8(){
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

void HongZhongLayer::selectFangka4(){
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

void HongZhongLayer::selectFangka16(){
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

void HongZhongLayer::selectAA(){
    if(NULL != getChildByTag(3024)){
        getChildByTag(3024)->setVisible(false);
    }
    if(NULL != getChildByTag(3025)){
        getChildByTag(3025)->setVisible(true);
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

void HongZhongLayer::selectFZ(){
    if(NULL != getChildByTag(3024)){
        getChildByTag(3024)->setVisible(true);
    }
    if(NULL != getChildByTag(3025)){
        getChildByTag(3025)->setVisible(false);
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

std::string HongZhongLayer::getPayWay(){
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

std::string HongZhongLayer::getOpenRoomJuShu(){
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


void HongZhongLayer :: openRoom(){
    std::string ftype = getOpenRoomJuShu();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterHongZhongCommand(ftype,getFanMa(),getDiFen(),ROOM_SIZE,getPayWay()));
}
void HongZhongLayer::openRoomByAgency(){
    std::string ftype = getOpenRoomJuShu();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterHongZhongCommand(ftype,getFanMa(),getDiFen(),ROOM_SIZE,UserData::getInstance()->getPoxiaoId()));
}

void HongZhongLayer::checkAgencyRecord(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendAgencyInfo("0"));
}

