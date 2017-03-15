//
//  YouMiClient.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/15.
//
//

#include "youmi/YouMiClient.hpp"

YouMiClient* YouMiClient::instance = NULL;

YouMiClient* YouMiClient::getInstance(){
    if(NULL == instance)
    {
        instance = new YouMiClient();
    }
    return instance;
}

YIMManager* YouMiClient::getYouMiManager(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return YIMManager::CreateInstance();
#endif
}
