//
//  RoomChatModule.hpp
//  Mahjong 游戏界面聊天显示
//
//  Created by qiuzhong on 16/8/8.
//
//

#ifndef ChatModule_hpp
#define ChatModule_hpp
#include "cocos2d.h"
#include "game/mahjong/state/GameData.h"
USING_NS_CC;

class ChatModule : public Node{

public:
    void onEnter() override;
    void onExit() override;
    virtual bool init();
    CREATE_FUNC(ChatModule);
private:
//    std::vector<ChatData> chatMsg;//聊天的消息队列
//    EventListenerCustom* roomChatListener;
};
#endif /* RoomChatModule_hpp */
