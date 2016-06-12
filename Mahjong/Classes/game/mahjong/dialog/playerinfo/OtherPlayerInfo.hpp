//
//  OtherPlayerInfo.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/18.
//
//

#ifndef OtherPlayerInfo_hpp
#define OtherPlayerInfo_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "game/mahjong/player/playerinfo/Player.h"
USING_NS_CC;
USING_NS_CC_EXT;

class OtherPlayerInfo : public Layer{
public:
    virtual bool init(Player* player);
    void onEnter() override;
    void onExit() override;
    static OtherPlayerInfo* create(Player* player);
private:
    Label* nickNameLabel;
    Sprite* playerGender;
    EventListenerCustom* addFriendRespListener2;
    void closeView();
    void addFriend(Ref* ref);
    CC_SYNTHESIZE(std::string, poxiaoId, PoxiaoId);

};
#endif /* OtherPlayerInfo_hpp */
