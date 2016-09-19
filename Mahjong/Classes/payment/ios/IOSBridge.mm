//
//  IOSBridge.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/19.
//
//

#include "payment/ios/IOSBridge.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "payment/ios/RechargeVC.h"
#endif

IOSBridge* IOSBridge::_instance = 0;

IOSBridge::IOSBridge(){
    this->init();
}

void IOSBridge::init(){
    //TODO
}

IOSBridge* IOSBridge::getInstance(){
    if (_instance == 0){
        _instance = new IOSBridge();
    }
    return _instance;
}

void IOSBridge::doPayEvent(int payId){
    log("HHHHHHHHHGGGGGGGGGGGGGGHHHHHHHHHHHH");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    RechargeVC *re = [[RechargeVC alloc] init];
    [re buy:1];
#endif
}