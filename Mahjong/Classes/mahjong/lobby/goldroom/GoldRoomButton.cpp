//
//  GoldRoomButton.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/12/20.
//
//

#include "mahjong/lobby/goldroom/GoldRoomButton.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/loading/Loading.h"
#include "server/NetworkManage.h"
#include "server/MsgConfig.h"

GoldRoomButton* GoldRoomButton::create(int roomid,int base,int hua){
    GoldRoomButton* cell = new GoldRoomButton();
    if(cell && cell->init(roomid,base,hua)){
        cell -> autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}

bool GoldRoomButton::init(int roomid, int base, int hua){
    if(!Sprite::init()){
        return false;
    }
    auto room_1 = MenuItemImage::create("mjlobby/gold_room_bnt_1.png", "mjlobby/gold_room_bnt_2.png", CC_CALLBACK_1(GoldRoomButton::openGoldRoom, this));
    room_1->setTag(roomid);
    auto roomSelect = Menu::create(room_1,NULL);
    roomSelect->setPosition(0,0);
    addChild(roomSelect);
    
    auto imag = Sprite::create(getImageByRoomId(roomid));
    imag->setPosition(-60,20);
    addChild(imag);
    
    auto huaText = Sprite::create("mjlobby/gold_hua.png");
    huaText->setPosition(110,-25);
    addChild(huaText);
    
    
    auto huaNum = LabelAtlas::create(StringUtils::format("%d",hua), "mjlobby/gold_fen_num.png", 13, 20, '0');
    huaNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    huaNum->setPosition(95,-25);
    addChild(huaNum);
    
    if(hua>10000){
        hua = hua/10000;
        huaNum->setString(StringUtils::format("%d",hua));
        auto wan =  Sprite::create("mjlobby/gold_wan.png");
        wan->setPosition(85,-25);
        addChild(wan);
        huaNum->setPosition(70,-25);
    }
    
    
    auto diText = Sprite::create("mjlobby/gold_di.png");
    diText->setPosition(20,-25);
    addChild(diText);
    
    auto diNum = LabelAtlas::create(StringUtils::format("%d",hua), "mjlobby/gold_fen_num.png", 13, 20, '0');
    diNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    diNum->setPosition(5,-25);
    addChild(diNum);
    
    if(base>10000){
        base = base/10000;
        diNum->setString(StringUtils::format("%d",base));
        auto wan =  Sprite::create("mjlobby/gold_wan.png");
        wan->setPosition(-5,-25);
        addChild(wan);
        diNum->setPosition(-20,-25);
    }
    
    
    return true;
}


void GoldRoomButton::openGoldRoom(Ref* ref){
    EventCustom imageEvent(MSG_LOBBY_SHOW_LOADING_LAYER);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&imageEvent);
    MenuItemImage* temp  = (MenuItemImage*) ref;
    log("openGoldRoom openGoldRoom openGoldRoom openGoldRoom openGoldRoom ");
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomCommand("1",StringUtils::format("%d",temp->getTag())));
    GAMEDATA::getInstance()->setCurrentSelectRoomId(temp->getTag());
}


std::string GoldRoomButton::getImageByRoomId(int roomId){
    if(roomId == ROOM_1){
        return "mjlobby/gold_room_one_1.png";
    }else if(roomId == ROOM_2){
        return "mjlobby/gold_room_one_2.png";
    }else if(roomId == ROOM_3){
        return "mjlobby/gold_room_one_3.png";
    }
    return "";
}
