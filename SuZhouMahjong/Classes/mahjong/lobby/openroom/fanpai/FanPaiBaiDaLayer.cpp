//
//  FanPaiBaiDaLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#include "mahjong/lobby/openroom/fanpai/FanPaiBaiDaLayer.hpp"
#include "mahjong/lobby/openroom/FriendOpenRoom.h"
#include "mahjong/common/state/GameData.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "mahjong/GameConfig.h"


bool FanPaiBaiDaLayer::init(){
    if(!Layer::init()){
        return false;
    }
    
    
    auto baiDaRoomText = Sprite::create("openroom/fanpaibaida_text.png");
    baiDaRoomText->setPosition(745,355);
    addChild(baiDaRoomText);
    
    
    /* 底和花的选择  */
    auto di_bg_1 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FanPaiBaiDaLayer::selectDifen1, this));
    auto menuDi_1 = Menu::create(di_bg_1,NULL);
    menuDi_1->setPosition(455,548);
    addChild(menuDi_1);
    //底花1/1
    auto diHuaImg11 = Sprite::create("openroom/circle_select.png");
    diHuaImg11->setTag(2001);
    diHuaImg11->setPosition(455,548);
    diHuaImg11->setVisible(true);
    addChild(diHuaImg11);
    
    
    auto di_bg_2 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FanPaiBaiDaLayer::selectDifen5, this));
    auto menuDi_2 = Menu::create(di_bg_2,NULL);
    menuDi_2->setPosition(650,548);
    addChild(menuDi_2);
    //底花2/2
    auto diHuaImg22 = Sprite::create("openroom/circle_select.png");
    diHuaImg22->setTag(2002);
    diHuaImg22->setPosition(650,548);
    diHuaImg22->setVisible(false);
    addChild(diHuaImg22);
    
    auto di_bg_3 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FanPaiBaiDaLayer::selectDifen10, this));
    auto menuDi_3 = Menu::create(di_bg_3,NULL);
    menuDi_3->setPosition(850,548);
    addChild(menuDi_3);
    //底花2/2
    auto diHuaImg33 = Sprite::create("openroom/circle_select.png");
    diHuaImg33->setTag(2003);
    diHuaImg33->setPosition(850,548);
    diHuaImg33->setVisible(false);
    addChild(diHuaImg33);
    
    
    /*门清选择*/
    auto youmeng = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FanPaiBaiDaLayer::selectYou, this));
    auto youmengMenu = Menu::create(youmeng,NULL);
    youmengMenu->setPosition(460,460);
    addChild(youmengMenu);
    
    auto youm = Sprite::create("openroom/circle_select.png");
    youm->setTag(4024);
    youm->setPosition(460,460);
    youm->setVisible(true);
    addChild(youm);
    
    auto wumeng = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FanPaiBaiDaLayer::selectWu, this));
    auto wumengMenu = Menu::create(wumeng,NULL);
    wumengMenu->setPosition(660,460);
    addChild(wumengMenu);
    
    auto wum = Sprite::create("openroom/circle_select.png");
    wum->setTag(4025);
    wum->setPosition(660,460);
    wum->setVisible(false);
    addChild(wum);
    
    /* 房间局数选择 */
    auto fangka8 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FanPaiBaiDaLayer::selectFangka8, this));
    auto fangka8Menu = Menu::create(fangka8,NULL);
    fangka8Menu->setPosition(460,330);
    addChild(fangka8Menu);
    
    auto select8 = Sprite::create("openroom/circle_select.png");
    select8->setTag(1024);
    select8->setPosition(460,330);
    select8->setVisible(true);
    addChild(select8);
    
    auto fangka4 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FanPaiBaiDaLayer::selectFangka4, this));
    auto fangka4Menu = Menu::create(fangka4,NULL);
    fangka4Menu->setPosition(660,330);
    addChild(fangka4Menu);
    
    auto select4 = Sprite::create("openroom/circle_select.png");
    select4->setTag(1025);
    select4->setPosition(660,330);
    select4->setVisible(false);
    addChild(select4);
    
    auto fangka16 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FanPaiBaiDaLayer::selectFangka16, this));
    auto fangka16Menu = Menu::create(fangka16,NULL);
    fangka16Menu->setPosition(850,330);
    addChild(fangka16Menu);
    
    auto select16 = Sprite::create("openroom/circle_select.png");
    select16->setTag(1026);
    select16->setPosition(850,330);
    select16->setVisible(false);
    addChild(select16);
    
    auto payByFZImg = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FanPaiBaiDaLayer::selectFZ, this));
    auto payByFZ = Menu::create(payByFZImg,NULL);
    payByFZ->setPosition(460,230);
    addChild(payByFZ);
    
    auto selectFZ = Sprite::create("openroom/circle_select.png");
    selectFZ->setTag(3024);
    selectFZ->setPosition(460,230);
    selectFZ->setVisible(true);
    addChild(selectFZ);
    
    auto payByAAImg = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FanPaiBaiDaLayer::selectAA, this));
    auto payByAAMenu = Menu::create(payByAAImg,NULL);
    payByAAMenu->setPosition(660,230);
    addChild(payByAAMenu);
    
    auto selectAA = Sprite::create("openroom/circle_select.png");
    selectAA->setTag(3025);
    selectAA->setPosition(660,230);
    selectAA->setVisible(false);
    addChild(selectAA);
    //开房消耗显示
    auto fangka = Label::createWithSystemFont(StringUtils::format("X%0.1f",atof(GAMEDATA::getInstance()->getKaiFangXiaoHao8().c_str())), "arial", 26);
    fangka->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fangka->setColor(Color3B(124,37,7));
    fangka->setPosition(975,230);
    fangka->setTag(1314);
    addChild(fangka);
    
    showOpenRoomBtn();
    
    if(UserData::getInstance()->getLatelyGameJuShu()=="4"){
        selectFangka4();
    }else if(UserData::getInstance()->getLatelyGameJuShu()=="16"){
        selectFangka16();
    }else{
        selectFangka8();
    }
    if(UserData::getInstance()->getLatelyFPDiFen() == "10"){
        selectDifen10();
    }else if(UserData::getInstance()->getLatelyFPDiFen() == "5"){
        selectDifen5();
    }else{
        selectDifen1();
    }
    
    if(UserData::getInstance()->getLatelyFPMenQing() == "0"){
        selectWu();
    }else{
        selectYou();
    }
    if(UserData::getInstance()->getLatelyPayWayAA()){
        FanPaiBaiDaLayer::selectAA();
    }else{
        FanPaiBaiDaLayer::selectFZ();
    }
    return true;
}

void FanPaiBaiDaLayer::showOpenRoomBtn(){
    auto openBtn = MenuItemImage::create("openroom/open_room_btn_img_1.png", "openroom/open_room_btn_img_2.png", CC_CALLBACK_0(FanPaiBaiDaLayer::openRoom, this));
    auto openMenu = Menu::create(openBtn,NULL);
    openMenu->setPosition(640,85);
    addChild(openMenu);
    
    if(UserData::getInstance()->getIsAgency()){
        openMenu->setPosition(300,85);
        
        auto agencyBtn = MenuItemImage::create("openroom/angecy_open_room_1.png", "openroom/angecy_open_room_2.png", CC_CALLBACK_0(FanPaiBaiDaLayer::openRoomByAgency, this));
        auto agencyMenu = Menu::create(agencyBtn,NULL);
        agencyMenu->setPosition(640,85);
        addChild(agencyMenu);
        
        auto manageBtn = MenuItemImage::create("openroom/angecy_manage_room_1.png", "openroom/angecy_manage_room_2.png", CC_CALLBACK_0(FanPaiBaiDaLayer::checkAgencyRecord, this));
        auto manageMenu = Menu::create(manageBtn,NULL);
        manageMenu->setPosition(990,85);
        addChild(manageMenu);
    }
}

void FanPaiBaiDaLayer::selectDifen1(){
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

void FanPaiBaiDaLayer::selectDifen5(){
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

void FanPaiBaiDaLayer::selectDifen10(){
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




void FanPaiBaiDaLayer::selectYou(){
    if(NULL != getChildByTag(4024)){
        getChildByTag(4024)->setVisible(true);
    }
    if(NULL != getChildByTag(4025)){
        getChildByTag(4025)->setVisible(false);
    }
}
void FanPaiBaiDaLayer::selectWu(){
    if(NULL != getChildByTag(4024)){
        getChildByTag(4024)->setVisible(false);
    }
    if(NULL != getChildByTag(4025)){
        getChildByTag(4025)->setVisible(true);
    }
}

void FanPaiBaiDaLayer::selectAA(){
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

void FanPaiBaiDaLayer::selectFZ(){
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

std::string FanPaiBaiDaLayer::getPayWay(){
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

std::string FanPaiBaiDaLayer::getMengQing(){
    std::string mq = "1";
    if(NULL != getChildByTag(4024)&&getChildByTag(4024)->isVisible()){
        mq = "1";
    }else if(NULL != getChildByTag(4025)&&getChildByTag(4025)->isVisible()){
        mq = "0";
    }
    return mq;
}

std::string FanPaiBaiDaLayer::getDiFen(){
    std::string difen = "1";
    if(NULL != getChildByTag(2001)&&getChildByTag(2001)->isVisible()){
        difen = "1";
    }else if(NULL != getChildByTag(2002)&&getChildByTag(2002)->isVisible()){
        difen = "5";
    }else if(NULL != getChildByTag(2003)&&getChildByTag(2003)->isVisible()){
        difen = "10";
    }
    return difen;
}

void FanPaiBaiDaLayer::selectFangka8(){
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
//    getChildByTag(1315)->setPosition(getChildByTag(1314)->getPositionX()+getChildByTag(1314)->getContentSize().width,237);
}

void FanPaiBaiDaLayer::selectFangka4(){
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
//    getChildByTag(1315)->setPosition(getChildByTag(1314)->getPositionX()+getChildByTag(1314)->getContentSize().width,237);
}

void FanPaiBaiDaLayer::selectFangka16(){
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
//    getChildByTag(1315)->setPosition(getChildByTag(1314)->getPositionX()+getChildByTag(1314)->getContentSize().width,237);
}

std::string FanPaiBaiDaLayer::getOpenRoomJuShu(){
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



void FanPaiBaiDaLayer :: openRoom(){
    std::string ftype = getOpenRoomJuShu();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFanPaiOpenRoomCommand(ftype,getMengQing(),getDiFen(),ROOM_SIZE,getPayWay()));
}

void FanPaiBaiDaLayer::openRoomByAgency(){
    std::string ftype = getOpenRoomJuShu();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFanPaiOpenRoomCommand(ftype,getMengQing(),getDiFen(),ROOM_SIZE,UserData::getInstance()->getPoxiaoId()));
}

void FanPaiBaiDaLayer::checkAgencyRecord(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendAgencyInfo("0"));
}



