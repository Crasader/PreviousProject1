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
    static OtherPlayerInfo* create(Player* player);
private:
    Label* nickNameLabel;
    Sprite* playerGender;
    void closeView();
    void addFriend();

};
#endif /* OtherPlayerInfo_hpp */
