//
//  GoldRoomPlate.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/25.
//
//

#include "mahjong/lobby/goldroom/GoldRoomPlate.hpp"
#include "mahjong/state/GameData.h"



bool GoldRoomPlate::init(){
    if(!Layer::init()){
        return false;
    }

    //添加点击事件
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GoldRoomPlate::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GoldRoomPlate::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    //绘制界面
    for(int i=(int)GAMEDATA::getInstance()->getRoomList().rooms.size()-1;i>=0;i--){
        GoldRoomButton* button = GoldRoomButton::create(GAMEDATA::getInstance()->getRoomList().rooms.at(i).roomId, GAMEDATA::getInstance()->getRoomList().rooms.at(i).hua, GAMEDATA::getInstance()->getRoomList().rooms.at(i).base);
        button->setPosition(1110,220+((int)GAMEDATA::getInstance()->getRoomList().rooms.size()-1-i)*120);
        addChild(button);
    
    }
    return true;
}

bool GoldRoomPlate::onTouchBegan(Touch *touch, Event  *event){
    return true;
}


void GoldRoomPlate::onTouchEnded(Touch *touch, Event  *event){
    if(NULL != getChildByTag(962)){
        if(!((Sprite*)getChildByTag(962))->getBoundingBox().containsPoint(touch->getLocation())){
            removeFromParent();
        }
    }
}
