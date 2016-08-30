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
    MenuItemToggle* act_tab_1;
    MenuItemToggle* act_tab_2;
    MenuItemToggle* act_tab_3;
    MenuItemToggle* act_tab_4;
    Sprite* tabLabel_1;
    Sprite* tabLabel_2;
    Sprite* tabLabel_3;
    Sprite* tabLabel_4;
    Layer* act_layer_1;
    Layer* act_layer_2;
    Layer* act_layer_3;
    Layer* act_layer_4;
    void initView();
    void closeView();
    void showActiviyContent();
    void showActivityRank();
    void showActivityPride();
    void showActivityRule();
};
#endif /* MahjongActivities_hpp */
