//
//  GoldRoomPlate.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/25.
//
//

#include "mahjong/lobby/goldroom/GoldRoomPlate.hpp"
#include "mahjong/common/state/GameData.h"


GoldRoomPlate* GoldRoomPlate::create(RoomListData data){
    GoldRoomPlate* cell = new GoldRoomPlate();
    if(cell && cell->init(data)){
        cell -> autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}


bool GoldRoomPlate::init(RoomListData data){
    if(!Layer::init()){
        return false;
    }

    //添加点击事件
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GoldRoomPlate::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GoldRoomPlate::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    //绘制界面
    for(int i=(int)(data.rooms.size()-1);i>=0;i--){
        GoldRoomButton* button = GoldRoomButton::create(data.rooms.at(i).roomId, data.rooms.at(i).hua, data.rooms.at(i).base);
        button->setPosition(675+((int)data.rooms.size()-1-i)*250,190);
        addChild(button);
    }
    return true;
}

bool GoldRoomPlate::onTouchBegan(Touch *touch, Event  *event){
    return false;
}


void GoldRoomPlate::onTouchEnded(Touch *touch, Event  *event){
    if(NULL != getChildByTag(962)){
        if(!((Sprite*)getChildByTag(962))->getBoundingBox().containsPoint(touch->getLocation())){
            removeFromParent();
        }
    }
}
