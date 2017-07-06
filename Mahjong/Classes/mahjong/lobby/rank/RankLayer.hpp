//
//  RankLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/6.
//
//

#ifndef RankLayer_hpp
#define RankLayer_hpp
#include "cocos2d.h"
#include "cocos-ext.h"
#include "mahjong/common/state/GameData.h"
#include "mahjong/lobby/rank/RankListA.hpp"
#include "mahjong/lobby/rank/RankListB.hpp"
#include "mahjong/lobby/rank/RankListC.hpp"
USING_NS_CC;
USING_NS_CC_EXT;

class RankLayer : public Layer{
public:
    bool init(LobbyPaiHangData data);
    void onEnter() override;
    void onExit() override;
    void onEnterTransitionDidFinish() override;
    static RankLayer* create(LobbyPaiHangData data);
private:
    EventListenerCustom* updateRank;
    Label* rankName1;
    Label* rankName2;
    Label* rankName3;
    MenuItemImage* tab1;
    MenuItemImage* tab2;
    MenuItemImage* tab3;
    RankListA* ranA ;
    RankListB* ranB;
    RankListC* ranC ;
    void shareToFriend();
    void shareToSocial();
    void showRank1();
    void showRank2();
    void showRank3();
};
#endif /* RankLayer_hpp */
