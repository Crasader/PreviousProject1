//
//  RoomChatModule.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/8.
//
//

#include "ChatModule.hpp"


bool ChatModule::init(){
    if(!Layer::init()){
        return false;
    }
    return true;
}


void ChatModule::onEnter(){
    Layer::onEnter();
    roomChatListener =  EventListenerCustom::create("", [=](EventCustom* event){
        
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(roomChatListener, 1);
}

void ChatModule::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(roomChatListener);
}

void ChatModule::showQuickText(std::string msg){
    
    
}



