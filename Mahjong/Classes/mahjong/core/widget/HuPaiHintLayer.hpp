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
#include "mahjong/jong/Jong.h"
#include "mahjong/state/GameData.h"
#include "mahjong/player/PlayerHero.h"
USING_NS_CC;

class HuPaiHintLayer : public Layer{
public:
    static HuPaiHintLayer* create(Vector<Jong*> playerHandJongs,std::vector<HeroHuPaiData> heroHu,PlayerHero* playerHero);
    bool init(Vector<Jong*> playerHandJongs,std::vector<HeroHuPaiData> heroHu,PlayerHero* playerHero);
    
};
#endif /* HuPaiHintLayer_hpp */
