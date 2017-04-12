//
//  FanMaAnim.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/4/12.
//
//

#include "mahjong/gameview/anim/FanMaAnim.hpp"

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
    auto text  = Sprite::create();
    text->setPosition(640,320);
    addChild(text);
    showTextAnim(text);
    
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
    animation->setDelayPerUnit(1.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action,CallFunc::create([=](){
        sprite->setVisible(false);
    }), NULL));
    
}
