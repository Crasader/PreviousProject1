//
//  FaceChatLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/16.
//
//

#include "game/mahjong/chat/FaceChatLayer.hpp"


bool FaceChatLayer::init(){
    if(!Layer::init()){
        return false;
    }
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(FaceChatLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(FaceChatLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(FaceChatLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
    
    auto faceChatBg = Sprite::create("chat/chat_text_box.png");
    faceChatBg->setTag(1001);
    faceChatBg->setPosition(Vec2(830,245));
    addChild(faceChatBg);
    
    auto faceMenu = Menu::create();
    for (int i = 0; i < 23; i++){
        std::string image_name = cocos2d::String::createWithFormat("chat/face_%d.png",i+1)->_string;
        MenuItemImage* face = MenuItemImage::create(image_name, image_name, CC_CALLBACK_1(FaceChatLayer::faceSelected,this));
        faceMenu->addChild(face);
        face->setTag(i+1);
        face->setPosition(705 + 50 * (i%6), 320-i/6*50);
    }
    faceMenu->setPosition(0,0);
    addChild(faceMenu);
    
    return true;
}

bool FaceChatLayer::onTouchBegan(Touch *touch, Event  *event){
    return true;
}

void FaceChatLayer:: onTouchMoved(Touch *touch, Event  *event){
    
}

void FaceChatLayer:: onTouchEnded(Touch *touch, Event  *event){
    Rect rect = ((Sprite*)getChildByTag(1001))->getBoundingBox();
    if(!rect.containsPoint(touch->getLocation())){
        removeFromParent();
    }
    
}

void FaceChatLayer::faceSelected(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*)ref;
}