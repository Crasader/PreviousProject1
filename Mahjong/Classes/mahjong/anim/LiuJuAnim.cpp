//
//  LiuJuAnim.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/24.
//
//

#include "mahjong/anim/LiuJuAnim.hpp"
#include "mahjong/utils/SeatIdUtil.h"
#include "mahjong/gameview/normal/MahjongView.h"

bool LiuJuAnim::init(){
    if(!Layer::init()){
        return false;
    }
    showLiuJuAnim();
    return true;
}


void LiuJuAnim::showLiuJuAnim(){
    auto paixinBg = Sprite::create("result/second_bg.png");
    paixinBg->setPosition(640,260);
    addChild(paixinBg);
    paixinBg->setOpacity(77);
    paixinBg->setScaleY(2.0f);
    paixinBg->runAction(Sequence::create(FadeTo::create(3.0/24, 255), NULL));
    
    auto xing = Sprite::create("gameview/liuju.png");
    addChild(xing);
    xing->setOpacity(77);
    xing->setScale(3.0f);
    xing->setPosition(640 ,260);
    xing->runAction(Sequence::create(DelayTime::create((5.0f/24)),Spawn::create(ScaleTo::create(3.0/24, 0.8f),FadeTo::create(3.0f/24, 255), NULL),ScaleTo::create(2.0/24, 1.0f), NULL));
    //光效动画
    Point pos1 = Point(200,260);
    Point pos2 = Point(1000,260);
    Sprite* guangXiao1 = Sprite::create("result/hupai_light.png");
    guangXiao1->setPosition(pos1);
    guangXiao1->setOpacity(77);
    addChild(guangXiao1);
    guangXiao1->runAction(Sequence::create(CallFunc::create([=](){
        if(!GAMEDATA::getInstance()->getIsFuPan()){
            ((MahjongView*)getParent())->showHandPokerOver(GAMEDATA::getInstance()->getHeroSeatId());
        }
    }),DelayTime::create(12.0f/24),Spawn::create(ScaleTo::create(5.0/24, 2.0f,2.0f),MoveTo::create(5.0/24, pos2),FadeTo::create(5.0/24, 200),NULL),Spawn::create(ScaleTo::create(5.0/24, 1.0f,1.0f),MoveTo::create(5.0/24, pos2), FadeTo::create(5.0/24, 0), NULL),NULL));
    
}
