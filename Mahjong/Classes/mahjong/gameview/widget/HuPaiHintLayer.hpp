//
//  HuPaiHintLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/2.
//
//

#ifndef HuPaiHintLayer_hpp
#define HuPaiHintLayer_hpp
#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "mahjong/common/jong/Jong.h"
#include "mahjong/common/state/GameData.h"
#include "mahjong/gameview/player/PlayerHero.h"
USING_NS_CC;
USING_NS_CC_EXT;

class HuPaiHintLayer : public Layer{
public:
    static HuPaiHintLayer* create(HeroHuPaiData heroHu,PlayerHero* playerHero);
    bool init(HeroHuPaiData heroHu,PlayerHero* playerHero);
private:
    
};
#endif /* HuPaiHintLayer_hpp */
