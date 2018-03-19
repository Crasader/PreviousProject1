//
//  PlayerResultCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#ifndef FPGameResultCell_hpp
#define FPGameResultCell_hpp
#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;

class FPGameResultCell : public Sprite{
public:
    static FPGameResultCell* create(GameResultData data);
    virtual bool init(GameResultData data);
    
};

#endif /* PlayerResultCell_hpp */
