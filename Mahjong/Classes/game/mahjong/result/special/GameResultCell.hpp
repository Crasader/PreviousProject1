//
//  PlayerResultCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#ifndef GameResultCell_hpp
#define GameResultCell_hpp
#include "cocos2d.h"
#include "game/mahjong/state/GameData.h"
USING_NS_CC;

class GameResultCell : public Sprite{
public:
    static GameResultCell* create(GameResultData data);
    virtual bool init(GameResultData data);
    
};

#endif /* PlayerResultCell_hpp */
