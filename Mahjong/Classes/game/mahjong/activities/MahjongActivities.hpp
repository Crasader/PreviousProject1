//
//  MahjongActivities.hpp
//  Mahjong
//  麻将活动
//  Created by qiuzhong on 16/8/30.
//
//

#ifndef MahjongActivities_hpp
#define MahjongActivities_hpp
#include "cocos2d.h"
USING_NS_CC;

class MahjongActivities : public Layer{
public:
    virtual bool init();
    void onEnter() override;
    void onExit() override;
    CREATE_FUNC(MahjongActivities);
private:
    void initView();
    void closeView();
    void showActiviyContent(Ref* ref);
    void showActivityRank(Ref* ref);
    void showActivityPride(Ref* ref);
    void showActivityRule(Ref* ref);
};
#endif /* MahjongActivities_hpp */
