//
//  RoomChatModule.hpp
//  Mahjong 游戏界面聊天显示
//
//  Created by qiuzhong on 16/8/8.
//
//

#ifndef RoomChatModule_hpp
#define RoomChatModule_hpp
#include "cocos2d.h"
USING_NS_CC;

class RoomChatModule : public Layer{

public:
    void onEnter() override;
    void onExit() override;
    virtual bool init();
    CREATE_FUNC(RoomChatModule);
private:
    EventListenerCustom* roomChatListener;
    void showQuickText(std::string msg);
};
#endif /* RoomChatModule_hpp */
