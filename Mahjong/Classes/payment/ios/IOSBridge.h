//
//  IOSBridge.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/19.
//
//

#ifndef IOSBridge_hpp
#define IOSBridge_hpp

#include "cocos2d.h"
using namespace cocos2d;

class IOSBridge{
public:
    static IOSBridge* getInstance();
    void doPayEvent(int payId);
private:
    IOSBridge();
    static IOSBridge* _instance;
    void init();
};
#endif /* IOSBridge_hpp */
