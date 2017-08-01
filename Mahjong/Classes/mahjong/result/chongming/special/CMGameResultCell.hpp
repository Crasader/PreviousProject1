//
//  PlayerResultCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#ifndef CMGameResultCell_hpp
#define CMGameResultCell_hpp
#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;

class CMGameResultCell : public Sprite{
public:
    static CMGameResultCell* create(GameResultData data);
    virtual bool init(GameResultData data);
    
};

#endif /* PlayerResultCell_hpp */
