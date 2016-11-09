//
//  GoldRoomPlate.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/25.
//
//

#include "game/mahjong/lobby/GoldRoomPlate.hpp"
#include "game/mahjong/state/GameData.h"
#include "server/NetworkManage.h"


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
    auto plateBg = Sprite::create("mjlobby/gold_plate_bg.png");
    plateBg->setTag(962);
    plateBg->setPosition(1110,320);
    addChild(plateBg);
    auto room_1 = MenuItemImage::create("mjlobby/gold_room_one_1.png", "mjlobby/gold_room_one_2.png", CC_CALLBACK_0(GoldRoomPlate::openRoomOne, this));
    auto room_2 = MenuItemImage::create("mjlobby/gold_room_two_1.png", "mjlobby/gold_room_two_2.png", CC_CALLBACK_0(GoldRoomPlate::openRoomTwo, this));
    auto room_3 = MenuItemImage::create("mjlobby/gold_room_three_1.png", "mjlobby/gold_room_three_2.png", CC_CALLBACK_0(GoldRoomPlate::openRoomThree, this));
    
    auto roomSelect = Menu::create(room_1,room_2,room_3,NULL);
    roomSelect->setPosition(1110,320);
    roomSelect->alignItemsVerticallyWithPadding(2);
    addChild(roomSelect);
    scheduleUpdate();
    
    return true;
}


void GoldRoomPlate::update(float dt){
    clickTime += dt;
    if(clickTime>3){
        isButtonCilckable = true;
    }
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

void GoldRoomPlate::openRoomOne(){
    if(checkCilckabale()){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomCommand("1",StringUtils::format("%d",ROOM_1)));
        GAMEDATA::getInstance()->setCurrentSelectRoomId(ROOM_1);
        isButtonCilckable = false;
        clickTime = 0;
    }
}


void GoldRoomPlate::openRoomTwo(){
    if(checkCilckabale()){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomCommand("1",StringUtils::format("%d",ROOM_2)));
        GAMEDATA::getInstance()->setCurrentSelectRoomId(ROOM_2);
        isButtonCilckable = false;
        clickTime = 0;
    }
}


void GoldRoomPlate::openRoomThree(){
    if(checkCilckabale()){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomCommand("1",StringUtils::format("%d",ROOM_3)));
        GAMEDATA::getInstance()->setCurrentSelectRoomId(ROOM_3);
        isButtonCilckable = false;
        clickTime = 0;
    }
}

bool GoldRoomPlate::checkCilckabale(){
    return isButtonCilckable;
}