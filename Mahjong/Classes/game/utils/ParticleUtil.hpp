//
//  ParticleUtil.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/13.
//
//

#ifndef ParticleUtil_hpp
#define ParticleUtil_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

enum MyParticleType{
    goldOnly,
    diamondOnly,
    lequanOnly,
    goldAndLequan,
    goldAndDianmond,
    lequanAndDiamond,
    three
};

class ParticleUtil : public Node{
public:
    static ParticleUtil* create(MyParticleType type);
    virtual bool init(MyParticleType type);
private:
    void showLequanExplosion();
    void showGoldExplosion();
    void showDiamondExplosion();
    void showGoldAndLequanExplosion();
    void showGoldAndDiamondExplosion();
    void showLequnaAndDiamondExplosion();
    void showThreeExplosion();

};
#endif /* ParticleUtil_hpp */
