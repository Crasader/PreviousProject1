//
//  BaiDaLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#include "mahjong/lobby/openroom/baida/BaiDaLayer.hpp"
#include "mahjong/lobby/openroom/FriendOpenRoom.h"
#include "mahjong/common/state/GameData.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "mahjong/GameConfig.h"


bool BaiDaLayer::init(){
    if(!Layer::init()){
        return false;
    }
    
    
    auto baiDaRoomText = Sprite::create("openroom/baida_text.png");
    baiDaRoomText->setPosition(745,355);
    addChild(baiDaRoomText);
    
    //自摸胡
    auto zimohu = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(BaiDaLayer::selectZiMoHu, this));
    auto zimohuMenu = Menu::create(zimohu,NULL);
    zimohuMenu->setPosition(460,420);
    addChild(zimohuMenu);
    
    auto selectZimohu = Sprite::create("openroom/icon_right.png");
    selectZimohu->setTag(4001);
    selectZimohu->setPosition(460,420);
    selectZimohu->setVisible(false);
    addChild(selectZimohu);
    
    //七对胡
    
    auto qiduihu = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(BaiDaLayer::selectQiDuiHu, this));
    auto qiduihuMenu = Menu::create(qiduihu,NULL);
    qiduihuMenu->setPosition(855,420);
    addChild(qiduihuMenu);
    
    auto selectQiduihu = Sprite::create("openroom/icon_right.png");
    selectQiduihu->setTag(4002);
    selectQiduihu->setPosition(855,420);
    selectQiduihu->setVisible(false);
    addChild(selectQiduihu);
    
    //翻拍选择
    auto fanpan0 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(BaiDaLayer::selectFanPaiZero, this));
    auto menuFanpai0 = Menu::create(fanpan0,NULL);
    menuFanpai0->setPosition(460,335);
    addChild(menuFanpai0);
    auto ImgFanpai0 = Sprite::create("openroom/circle_select.png");
    ImgFanpai0->setTag(2001);
    ImgFanpai0->setPosition(460,335);
    ImgFanpai0->setVisible(true);
    addChild(ImgFanpai0);
    
    auto fanpan2 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(BaiDaLayer::selectFanPaiTwo, this));
    auto menuFanpai2 = Menu::create(fanpan2,NULL);
    menuFanpai2->setPosition(660,335);
    addChild(menuFanpai2);
    auto ImgFanpai2 = Sprite::create("openroom/circle_select.png");
    ImgFanpai2->setTag(2002);
    ImgFanpai2->setPosition(660,335);
    ImgFanpai2->setVisible(false);
    addChild(ImgFanpai2);
    
    auto fanpan4 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(BaiDaLayer::selectFanPaiFour, this));
    auto menuFanpai4 = Menu::create(fanpan4,NULL);
    menuFanpai4->setPosition(850,335);
    addChild(menuFanpai4);
    auto ImgFanpai4 = Sprite::create("openroom/circle_select.png");
    ImgFanpai4->setTag(2003);
    ImgFanpai4->setPosition(850,335);
    ImgFanpai4->setVisible(false);
    addChild(ImgFanpai4);
    
    auto fanpan6 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(BaiDaLayer::selectFanPaiSix, this));
    auto menuFanpai6 = Menu::create(fanpan6,NULL);
    menuFanpai6->setPosition(1025,335);
    addChild(menuFanpai6);
    auto ImgFanpai6 = Sprite::create("openroom/circle_select.png");
    ImgFanpai6->setTag(2004);
    ImgFanpai6->setPosition(1025,335);
    ImgFanpai6->setVisible(false);
    addChild(ImgFanpai6);
    
    /* 房间局数选择 */
    auto fangka8 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(BaiDaLayer::selectFangka8, this));
    auto fangka8Menu = Menu::create(fangka8,NULL);
    fangka8Menu->setPosition(460,253);
    addChild(fangka8Menu);
    
    auto select8 = Sprite::create("openroom/circle_select.png");
    select8->setTag(1024);
    select8->setPosition(460,253);
    select8->setVisible(true);
    addChild(select8);
    
    auto fangka4 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(BaiDaLayer::selectFangka4, this));
    auto fangka4Menu = Menu::create(fangka4,NULL);
    fangka4Menu->setPosition(660,253);
    addChild(fangka4Menu);
    
    auto select4 = Sprite::create("openroom/circle_select.png");
    select4->setTag(1025);
    select4->setPosition(660,253);
    select4->setVisible(false);
    addChild(select4);
    
    auto fangka16 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(BaiDaLayer::selectFangka16, this));
    auto fangka16Menu = Menu::create(fangka16,NULL);
    fangka16Menu->setPosition(850,253);
    addChild(fangka16Menu);
    
    auto select16 = Sprite::create("openroom/circle_select.png");
    select16->setTag(1026);
    select16->setPosition(850,253);
    select16->setVisible(false);
    addChild(select16);
    
    auto payByFZImg = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(BaiDaLayer::selectFZ, this));
    auto payByFZ = Menu::create(payByFZImg,NULL);
    payByFZ->setPosition(460,175);
    addChild(payByFZ);
    
    auto selectFZ = Sprite::create("openroom/circle_select.png");
    selectFZ->setTag(3024);
    selectFZ->setPosition(460,175);
    selectFZ->setVisible(true);
    addChild(selectFZ);
    
    auto payByAAImg = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(BaiDaLayer::selectAA, this));
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
    
    //按照记录显示用户的习惯
    if(UserData::getInstance()->getLatelyGameJuShu()=="4"){
        selectFangka4();
    }else if(UserData::getInstance()->getLatelyGameJuShu()=="16"){
        selectFangka16();
    }else{
        selectFangka8();
    }
    if(UserData::getInstance()->getLatelyBDZiMo() == "1"){
        selectZimohu->setVisible(true);
    }else{
        selectZimohu->setVisible(false);
    }
    if(UserData::getInstance()->getLatelyBDQiDui() == "1"){
        selectQiduihu->setVisible(true);
    }else{
        selectQiduihu->setVisible(false);
    }
    if(GAMEDATA::getInstance()->getPrivateFanPai() == "2"){
        selectFanPaiTwo();
    }else if(GAMEDATA::getInstance()->getPrivateFanPai() == "4"){
        selectFanPaiFour();
    }else if(GAMEDATA::getInstance()->getPrivateFanPai() == "6"){
        selectFanPaiSix();
    }else{
        selectFanPaiZero();
    }
    if(UserData::getInstance()->getLatelyPayWayAA()){
        BaiDaLayer::selectAA();
    }else{
        BaiDaLayer::selectFZ();
    }
    
    return true;
}

void BaiDaLayer::showOpenRoomBtn(){
    auto openBtn = MenuItemImage::create("openroom/open_room_btn_img_1.png", "openroom/open_room_btn_img_2.png", CC_CALLBACK_0(BaiDaLayer::openRoom, this));
    auto openMenu = Menu::create(openBtn,NULL);
    openMenu->setPosition(640,85);
    addChild(openMenu);
    
    if(UserData::getInstance()->getIsAgency()){
        openMenu->setPosition(300,85);
        
        auto agencyBtn = MenuItemImage::create("openroom/angecy_open_room_1.png", "openroom/angecy_open_room_2.png", CC_CALLBACK_0(BaiDaLayer::openRoomByAgency, this));
        auto agencyMenu = Menu::create(agencyBtn,NULL);
        agencyMenu->setPosition(640,85);
        addChild(agencyMenu);
        
        auto manageBtn = MenuItemImage::create("openroom/angecy_manage_room_1.png", "openroom/angecy_manage_room_2.png", CC_CALLBACK_0(BaiDaLayer::checkAgencyRecord, this));
        auto manageMenu = Menu::create(manageBtn,NULL);
        manageMenu->setPosition(990,85);
        addChild(manageMenu);
    }
}

void BaiDaLayer::selectZiMoHu(){
    if(NULL != getChildByTag(4001)){
        getChildByTag(4001)->setVisible(!getChildByTag(4001)->isVisible());
    }
    
}

void BaiDaLayer::selectQiDuiHu(){
    if(NULL != getChildByTag(4002)){
        getChildByTag(4002)->setVisible(!getChildByTag(4002)->isVisible());
    }
}

void BaiDaLayer::selectFanPaiZero(){
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
}
void BaiDaLayer::selectFanPaiTwo(){
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
    
}
void BaiDaLayer::selectFanPaiFour(){
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
    
}
void BaiDaLayer::selectFanPaiSix(){
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
    
}

void BaiDaLayer::selectAA(){
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

void BaiDaLayer::selectFZ(){
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

std::string BaiDaLayer::getPayWay(){
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

std::string BaiDaLayer::getFanPai(){
    std::string fanapi = "0";
    if(NULL != getChildByTag(2001)&&getChildByTag(2001)->isVisible()){
        fanapi  = "0";
    }else if(NULL != getChildByTag(2002)&&getChildByTag(2002)->isVisible()){
        fanapi  = "2";
    }else if(NULL != getChildByTag(2003)&&getChildByTag(2003)->isVisible()){
        fanapi  = "4";
    }else if(NULL != getChildByTag(2004)&&getChildByTag(2004)->isVisible()){
        fanapi  = "6";
    }
    return fanapi;
    
}

std::string BaiDaLayer::getOnlyZimo(){
    std::string zimo = "0";
    if(NULL != getChildByTag(4001)){
        if(getChildByTag(4001)->isVisible()){
            zimo = "1";
        }else{
            zimo = "0";
        }
    }
    return zimo;
    
}

std::string BaiDaLayer::getQiDui(){
    std::string qidui = "0";
    if(NULL != getChildByTag(4002)){
        if(getChildByTag(4002)->isVisible()){
            qidui = "1";
        }else{
            qidui = "0";
        }
    }
    return qidui;
}

void BaiDaLayer::selectFangka8(){
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

void BaiDaLayer::selectFangka4(){
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

void BaiDaLayer::selectFangka16(){
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

std::string BaiDaLayer::getOpenRoomJuShu(){
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


void BaiDaLayer :: openRoom(){
    std::string ftype = getOpenRoomJuShu();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBDOpenRoomCommand(ftype,getOnlyZimo(),getQiDui(),getFanPai(),ROOM_SIZE,getPayWay()));
}

void BaiDaLayer::openRoomByAgency(){
    std::string ftype = getOpenRoomJuShu();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBDOpenRoomCommand(ftype,getOnlyZimo(),getQiDui(),getFanPai(),ROOM_SIZE,UserData::getInstance()->getPoxiaoId()));
}

void BaiDaLayer::checkAgencyRecord(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendAgencyInfo("0"));
}




