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
    auto room_1 = MenuItemImage::create("mjlobby/competition_1_2.png", "mjlobby/competition_1_2.png", CC_CALLBACK_1(GoldRoomButton::openGoldRoom, this));
    room_1->setTag(roomid);
    auto roomSelect = Menu::create(room_1,NULL);
    roomSelect->setPosition(0,0);
    addChild(roomSelect);
//    
//    auto imag = Sprite::create(getImageByRoomId(roomid));
//    imag->setPosition(-65,20);
//    addChild(imag);
//    
//    auto roomtext = Label::createWithSystemFont("(上海敲麻)", "arial", 20);
//    roomtext->setColor(Color3B(211,232,255));
//    roomtext->setPosition(65,20);
//    addChild(roomtext);
//    
//    
//    auto diNum = LabelAtlas::create(StringUtils::format("%d",base), "mjlobby/gold_room_num_label.png", 20, 26, '0');
//    diNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    diNum->setPosition(-140,-25);
//    addChild(diNum);
//    
//    auto diText = Sprite::create("mjlobby/gold_di.png");
//    diText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    diText->setPosition(diNum->getPositionX()+diNum->getContentSize().width-5,-25);
//    addChild(diText);
//    
//    
//    
//    auto huaNum = LabelAtlas::create(StringUtils::format("%d",hua), "mjlobby/gold_room_num_label.png", 20, 26, '0');
//    huaNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    huaNum->setPosition(diText->getPositionX()+diText->getContentSize().width+20,-25);
//    addChild(huaNum);
//    
//    auto huaText = Sprite::create("mjlobby/gold_hua.png");
//    huaText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    huaText->setPosition(huaNum->getPositionX()+huaNum->getContentSize().width-5,-25);
//    addChild(huaText);
    
    
    return true;
}


void GoldRoomButton::openGoldRoom(Ref* ref){
    EventCustom imageEvent(MSG_LOBBY_SHOW_LOADING_LAYER);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&imageEvent);
    MenuItemImage* temp  = (MenuItemImage*) ref;
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomCommand("1",StringUtils::format("%d",temp->getTag())));
    GAMEDATA::getInstance()->setCurrentSelectRoomId(temp->getTag());
}


std::string GoldRoomButton::getImageByRoomId(int roomId){
    return "mjlobby/gold_room_text.png";
}
