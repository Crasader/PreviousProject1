//
//  DayCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/20.
//
//

#ifndef DayCell_hpp
#define DayCell_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "game/mahjong/state/GameData.h"
USING_NS_CC;

class DayCell :public Sprite{
public:
    static DayCell* create(int propType);
    virtual bool init(int propType);
    void setDayState(int type);
    void startAnimate();
    void showPropResult(PrideData data);
private:
    void update(float dt);
    int half;
    };
#endif /* DayCell_hpp */
