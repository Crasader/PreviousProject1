//
//  FanMaAnim.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/4/12.
//
//

#include "mahjong/gameview/anim/FanMaAnim.hpp"
#include "mahjong/common/jong/Jong.h"

FanMaAnim* FanMaAnim::create(std::vector<std::string> mas){
    FanMaAnim* anim = new FanMaAnim();
    if(anim && anim->init(mas)){
        anim->autorelease();
        return anim;
    }
    CC_SAFE_DELETE(anim);
    return NULL;
}

bool FanMaAnim::init(std::vector<std::string> mas){
    if(!Layer::init()){
        return false;
    }
   
    
    auto animStep1 = CallFunc::create([=](){
        auto text  = Sprite::create();
        text->setPosition(640,320);
        addChild(text);
        showTextAnim(text);
    });
    
    auto animStep2 = DelayTime::create(1.0f);
    
    auto animSetp3 = CallFunc::create([=](){
        auto anim = Sprite::create();
        anim->setPosition(640-70*mas.size()/2+index*70,360);
        addChild(anim);
        showFanPai(anim);
    });
    
    auto animStep4  = DelayTime::create(0.75f);
    
    auto animStep5 = CallFunc::create([=](){
        Jong* bigJong = Jong::create();
        bigJong->showJong(playedshow, atoi(mas.at(index).c_str()));
        bigJong->setPosition(640-70*mas.size()/2+index*70,360);
        bigJong->setScale(0.9);
        addChild(bigJong);
        index++;
    });
    
    auto seq1 =Sequence::create(animSetp3,animStep4,animStep5,NULL);
    auto seq2 =Sequence::create(animStep1,animStep2,Repeat::create(seq1, mas.size()),NULL);
    auto shuzhu = Sprite::create();
    addChild(shuzhu);
    shuzhu->runAction(seq2);
    
    return  true;
}

void FanMaAnim::showTextAnim(Sprite* sprite){
    auto animation = Animation::create();
    std::string index;
    for( int i=1;i<=16;i++)
    {
        
        if(i<10){
            index = StringUtils::format("0%d",i);
        }else{
            index = StringUtils::format("%d",i);
        }
        std::string imageName = StringUtils::format ("fanma/fanma_00%s.png",index.c_str());
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(2.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action,CallFunc::create([=](){
        sprite->setVisible(false);
    }), NULL));
}

void FanMaAnim::showFanPai(Sprite* sprite){
    auto animation = Animation::create();
    std::string index;
    for( int i=1;i<=6;i++)
    {
        
        std::string imageName = StringUtils::format ("fanma/dapai_%d.png",i);
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(3.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action,CallFunc::create([=](){
        sprite->setVisible(false);
    }), NULL));
    
}


