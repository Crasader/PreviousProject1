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
    imag->setPosition(-55,20);
    addChild(imag);
    
    auto huaText = Sprite::create("mjlobby/gold_hua.png");
    huaText->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    huaText->setPosition(110,-25);
    addChild(huaText);
    
    auto huaNum = LabelAtlas::create(StringUtils::format("%d",hua), "mjlobby/gold_fen_num.png", 13, 20, '0');
    huaNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    huaNum->setPosition(huaText->getPositionX()-huaText->getContentSize().width,-25);
    addChild(huaNum);
    
    
    auto diText = Sprite::create("mjlobby/gold_di.png");
    diText->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    diText->setPosition(huaNum->getPositionX()-huaNum->getContentSize().width-10,-25);
    addChild(diText);
    
    auto diNum = LabelAtlas::create(StringUtils::format("%d",base), "mjlobby/gold_fen_num.png", 13, 20, '0');
    diNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    diNum->setPosition(diText->getPositionX()-diText->getContentSize().width,-25);
    addChild(diNum);

    return true;
}


void GoldRoomButton::openGoldRoom(Ref* ref){
    EventCustom imageEvent(MSG_LOBBY_SHOW_LOADING_LAYER);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&imageEvent);
    MenuItemImage* temp  = (MenuItemImage*) ref;
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomCommand("1",StringUtils::format("%d",temp->getTag())));
}


std::string GoldRoomButton::getImageByRoomId(int roomId){
    if(roomId == 1002){
        return "mjlobby/gold_room_one_2.png";
    }else {
        return "mjlobby/gold_room_one_1.png";
    }
}
