//
//  RoomChatModule.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/8.
//
//

#include "RoomChatModule.hpp"


bool RoomChatModule::init(){
    if(!Layer::init()){
        return false;
    }
    return true;
}


void RoomChatModule::onEnter(){
    Layer::onEnter();
    roomChatListener =  EventListenerCustom::create("", [=](EventCustom* event){
        
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(roomChatListener, 1);
}

void RoomChatModule::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(roomChatListener);
}

void RoomChatModule::showQuickText(std::string msg){
    
    
}



