//
//  OtherPlayerInfo.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/18.
//
//

#ifndef OtherPlayerInfo_hpp
#define OtherPlayerInfo_hpp

#include "cocos2d.h"
#include "cocos-ext.h"
#include "mahjong/player/playerinfo/Player.h"
USING_NS_CC;
USING_NS_CC_EXT;

class OtherPlayerInfo : public Layer{
public:
    virtual bool init(Player* player);
    void onEnter() override;
    void onExit() override;
    static OtherPlayerInfo* create(Player* player);
private:
    void closeView();
    CC_SYNTHESIZE(Player*, player, Player);

};
#endif /* OtherPlayerInfo_hpp */
