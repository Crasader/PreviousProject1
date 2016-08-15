//
//  RoomChatModule.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/8.
//
//

#include "ChatModule.hpp"
#include "server/NetworkManage.h"


bool ChatModule::init(){
    if(!Node::init()){
        return false;
    }
    return true;
}


void ChatModule::onEnter(){
    Node::onEnter();
//    roomChatListener =  EventListenerCustom::create(MSG_PLAYER_CHAT_NOTIFY, [=](EventCustom* event){
//        
//    });
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(roomChatListener, 1);
}

void ChatModule::onExit(){
    Node::onExit();
//    Director::getInstance()->getEventDispatcher()->removeEventListener(roomChatListener);
}



