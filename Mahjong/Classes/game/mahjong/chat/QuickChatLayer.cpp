//
//  QuickChatLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/16.
//
//
#include "game/mahjong/chat/QuickChatLayer.hpp"


bool QuickChatLayer::init(){
    if(!Layer::init()){
        return false;
    }
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(QuickChatLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(QuickChatLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(QuickChatLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
    
    auto quickChatBg = Sprite::create("chat/quick_chat_bg.png");
    quickChatBg->setTag(1001);
    quickChatBg->setPosition(Vec2(605,295));
    addChild(quickChatBg);
    
    return true;
}

bool QuickChatLayer::onTouchBegan(Touch *touch, Event  *event){
    return true;
}

void QuickChatLayer:: onTouchMoved(Touch *touch, Event  *event){

}

void QuickChatLayer:: onTouchEnded(Touch *touch, Event  *event){
    Rect rect = ((Sprite*)getChildByTag(1001))->getBoundingBox();
    if(!rect.containsPoint(touch->getLocation())){
        removeFromParent();
    }
    
}