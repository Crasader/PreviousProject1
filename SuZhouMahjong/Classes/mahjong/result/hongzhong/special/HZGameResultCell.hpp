//
//  PlayerResultCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#ifndef HZ_GameResultCell_hpp
#define HZ_GameResultCell_hpp
#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;

class HZGameResultCell : public Sprite{
public:
    static HZGameResultCell* create(GameResultData data);
    virtual bool init(GameResultData data);
    
};

#endif /* PlayerResultCell_hpp */
