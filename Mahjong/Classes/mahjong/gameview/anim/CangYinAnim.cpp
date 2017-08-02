//
//  FanMaAnim.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/4/12.
//
//

#include "mahjong/gameview/anim/CangYinAnim.hpp"
#include "mahjong/common/jong/Jong.h"

CangYinAnim* CangYinAnim::create(std::string mas){
    CangYinAnim* anim = new CangYinAnim();
    if(anim && anim->init(mas)){
        anim->autorelease();
        return anim;
    }
    CC_SAFE_DELETE(anim);
    return NULL;
}

bool CangYinAnim::init(std::string mas){
    if(!Layer::init()){
        return false;
    }
   
    
    auto animStep1 = CallFunc::create([=](){
        auto text  = Sprite::create();
        text->setPosition(640,320);
        addChild(text,2);
         showTextAnim(text);
    });
    
    auto animStep2 = DelayTime::create(1.0f);
    
    auto animStep3 = CallFunc::create([=](){
        Jong* bigJong = Jong::create();
        bigJong->showJong(playedshow, atoi(mas.c_str()));
        bigJong->setPosition(640,350);
        bigJong->setScale(0.9);
        addChild(bigJong);
    });
    
    auto seq2 =Sequence::create(animStep1,animStep2,animStep3,NULL);
    auto shuzhu = Sprite::create();
    addChild(shuzhu);
    shuzhu->runAction(seq2);
    
    return  true;
}


void CangYinAnim::showTextAnim(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<=16;i++)
    {

        std::string imageName = StringUtils::format ("fanma/fcy_%d.png",i);
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(2.0f / 36.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action,CallFunc::create([=](){
        sprite->setVisible(false);
    }), NULL));
}


void CangYinAnim::showFanPai(Sprite* sprite){
    auto animation = Animation::create();
    std::string index;
    for( int i=1;i<=6;i++)
    {
        
        std::string imageName = StringUtils::format ("fanma/dapai_%d.png",i);
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(3.0f / 36.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action,CallFunc::create([=](){
        sprite->setVisible(false);
    }), NULL));
    
}


