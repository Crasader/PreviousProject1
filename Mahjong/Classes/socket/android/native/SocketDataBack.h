//
//  SocketDataBack.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/1/12.
//
//

#ifndef SocketDataBack_hpp
#define SocketDataBack_hpp

#include "cocos2d.h"
#include "userdata/UserData.h"

using namespace cocos2d;

class SocketDataBack{
public:
    static SocketDataBack* getInstance();
    void dealDataCallBack(std::string data);
    void onDisconnected();
private:
    SocketDataBack();
    static SocketDataBack* _instance;
};

#endif /* SocketDataBack_hpp */
