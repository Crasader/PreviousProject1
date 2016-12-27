//
//  PlayerResultCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#ifndef PlayerResultCell_hpp
#define PlayerResultCell_hpp
#include "cocos2d.h"
#include "mahjong/state/GameData.h"
USING_NS_CC;

class PlayerResultCell : public Sprite{
public:
    static PlayerResultCell* create(GameResultData data);
    virtual bool init(GameResultData data);
};

#endif /* PlayerResultCell_hpp */
