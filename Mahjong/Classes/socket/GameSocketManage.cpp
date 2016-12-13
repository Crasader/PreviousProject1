//
//  GameSocketManage.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/12/13.
//
//

#include "socket/GameSocketManage.hpp"
#import "socket/ios/CocoaSocketManage.h"

GameSocketManage* GameSocketManage::_instance = NULL;

GameSocketManage* GameSocketManage::getInstance(){
    
    if (_instance == NULL){
        _instance = new GameSocketManage();
    }
    return _instance;
}


void GameSocketManage::socketConnect(){
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    CocoaSocketManage::getInstance()->connectSocket();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
#endif
}
