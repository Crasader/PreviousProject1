//
//  PlayerResultCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#ifndef HZ_PlayerResultCell_hpp
#define HZ_PlayerResultCell_hpp
#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;

class HZPlayerResultCell : public Sprite{
public:
    static HZPlayerResultCell* create(GameResultData data);
    virtual bool init(GameResultData data);
};

#endif /* PlayerResultCell_hpp */
