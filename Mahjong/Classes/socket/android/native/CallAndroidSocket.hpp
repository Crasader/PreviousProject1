//
//  CallAndroidSocket.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/1/11.
//
//

#ifndef CallAndroidSocket_hpp
#define CallAndroidSocket_hpp
#include "cocos2d.h"
#include "userdata/UserData.h"

using namespace cocos2d;

class CallAndroidSocket{
public:
    static CallAndroidSocket* getInstance();
    void requestEvent(std::string poxiaoId,std::string payId);
private:
    std::string _jniPath;
    const char* getSocketJniPath();
    CallAndroidSocket();
    static CallAndroidSocket* _instance;
};
#endif /* CallAndroidSocket_hpp */
