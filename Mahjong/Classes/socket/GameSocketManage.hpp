//
//  GameSocketManage.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/12/13.
//
//

#ifndef GameSocketManage_hpp
#define GameSocketManage_hpp
#include "cocos2d.h"
USING_NS_CC;

class GameSocketManage{
public:
    static GameSocketManage* getInstance();
    bool socketConnect();
    void startSocketBeat(std::string send);
    void sendScoketData(std::string msg);
    void receiveScoketData(std::string msg);
    void resetBeatCount();
    void disConnectSocket();
    void disConnectSelf();
private:
    GameSocketManage();
    static GameSocketManage* _instance;
};
#endif /* GameSocketManage_hpp */
