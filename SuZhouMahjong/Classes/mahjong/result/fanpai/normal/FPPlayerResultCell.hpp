//
//  PlayerResultCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#ifndef FPPlayerResultCell_hpp
#define FPPlayerResultCell_hpp
#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;

class FPPlayerResultCell : public Sprite{
public:
    static FPPlayerResultCell* create(GameResultData data);
    virtual bool init(GameResultData data);
};

#endif /* PlayerResultCell_hpp */
