//
//  PlayerInfoCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/26.
//
//

#ifndef PlayerInfoCell_hpp
#define PlayerInfoCell_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameData.h"
USING_NS_CC;

class PlayerInfoCell : public Sprite{
public:
    static PlayerInfoCell* create(GameResultData data);
    virtual bool init(GameResultData data);
    
};
#endif /* PlayerInfoCell_hpp */
