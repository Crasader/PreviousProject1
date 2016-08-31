//
//  DayCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/20.
//
//

#ifndef DayCell_hpp
#define DayCell_hpp

#include "cocos2d.h"
#include "game/mahjong/state/GameData.h"
USING_NS_CC;

class DayCell :public Sprite{
public:
    static DayCell* create();
    virtual bool init();
    void setDayState(int type);
    void startAnimate();
    void showPropResult(PrideData data);
    void showPropResult2(PrideData data);
private:
    void update(float dt);
    int half;
    };
#endif /* DayCell_hpp */
