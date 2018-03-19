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
#include "mahjong/gameview/player/base/PlayerInfo.h"
USING_NS_CC;
USING_NS_CC_EXT;

class OtherPlayerInfo : public Layer{
public:
    virtual bool init(PlayerInfo* player);
    void onEnter() override;
    void onExit() override;
    static OtherPlayerInfo* create(PlayerInfo* player);
private:
    void closeView();
    CC_SYNTHESIZE(PlayerInfo*, player, PlayerInfo);

};
#endif /* OtherPlayerInfo_hpp */
