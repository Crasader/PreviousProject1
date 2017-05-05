//
//  LostNetwor'.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/12/2.
//
//

#include "mahjong/common/dialog/network/LostNetwork2.hpp"
#include "server/SocketDataManage.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "mahjong/lobby/LobbyScene.h"

bool LostNetwork2::init(){
    if(!Layer::init()){
        return false;
    }
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 125), 1280, 720);
    addChild(bg0, -1);
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto bg = Sprite::create("common/toast_bg_2.png");
    bg->setPosition(640,300);
    addChild(bg);
    
    auto showMsg = Label::createWithSystemFont("网络连接断开啦,正在努力重连中...", "Arial", 24);
    showMsg->setAnchorPoint(Point::ANCHOR_MIDDLE);
    showMsg->setPosition(640,300);
    addChild(showMsg);
    
    schedule([=](float dt){
        if(NetworkManage::getInstance()->reConnectSocket()){
            int  delayTime = 2.5f;
            schedule([=](float dt){
                if(UserData::getInstance()->getWxOpenId() ==  "unknow"){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getVistorLoginAgain(UserData::getInstance()->getUserName(), UserData::getInstance()->getPassword()));
                }else{
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(), UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(), StringUtils::format("%d",UserData::getInstance()->getGender()), UserData::getInstance()->getNickName(), UserData::getInstance()->getHsman(), UserData::getInstance()->getHstype(), UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer(),true));
                }
            }, 0, 0, delayTime, "socket_reconnect2000");
            NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
        }

    }, 10, 2, 10, "socket_reconnect5000");
    return true;
}
