//
//  LiuJuAnim.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/ 36.
//
//

#include "mahjong/gameview/anim/LiuJuAnim.hpp"
#include "mahjong/gameview/shanghai/normal/MahjongView.h"
#include "mahjong/gameview/hongzhong/normal/HongZhongView.hpp"
#include "mahjong/common/utils/SeatIdUtil.h"

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
    paixinBg->runAction(Sequence::create(FadeTo::create(3.0/ 36, 255), NULL));
    
    auto xing = Sprite::create("gameview/liuju.png");
    addChild(xing);
    xing->setOpacity(77);
    xing->setScale(3.0f);
    xing->setPosition(640 ,260);
    xing->runAction(Sequence::create(DelayTime::create((5.0f/ 36)),Spawn::create(ScaleTo::create(3.0/ 36, 0.8f),FadeTo::create(3.0f/ 36, 255), NULL),ScaleTo::create(2.0/ 36, 1.0f), NULL));
    //光效动画
    Point pos1 = Point(200,260);
    Point pos2 = Point(1000,260);
    Sprite* guangXiao1 = Sprite::create("result/hupai_light.png");
    guangXiao1->setPosition(pos1);
    guangXiao1->setOpacity(77);
    addChild(guangXiao1);
    guangXiao1->runAction(Sequence::create(CallFunc::create([=](){
        if(GAMEDATA::getInstance()->getGameType() == 1){
            ((MahjongView*)getParent())->showHandPokerOver(GAMEDATA::getInstance()->getHeroSeatId());
        }else if(GAMEDATA::getInstance()->getGameType() == 3){
            ((HongZhongView*)getParent())->showHandPokerOver(GAMEDATA::getInstance()->getHeroSeatId());
        }
    }),DelayTime::create(12.0f/ 36),Spawn::create(ScaleTo::create(5.0/ 36, 2.0f,2.0f),MoveTo::create(5.0/ 36, pos2),FadeTo::create(5.0/ 36, 200),NULL),Spawn::create(ScaleTo::create(5.0/ 36, 1.0f,1.0f),MoveTo::create(5.0/ 36, pos2), FadeTo::create(5.0/ 36, 0), NULL),NULL));
    
}
